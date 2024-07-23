/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_SYSTEM_ROUTINES_HPP
#define HORIZON_SYSTEM_ROUTINES_HPP

#include <boost/lockfree/spsc_queue.hpp>
#include <optional>
#include <vector>
#include <memory>
#include <map>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include <iostream>

class Server;
class MainframeComponent;
namespace Horizon
{
namespace System
{	
enum runtime_routine_chain_status : int
{
    RUNTIME_ROUTINE_CHAIN_NOT_STARTED = 0,
    RUNTIME_ROUTINE_CHAIN_STOPPED   = 1,
    RUNTIME_ROUTINE_CHAIN_FAILED    = 2,
    RUNTIME_ROUTINE_CHAIN_PAUSED    = 3,
    RUNTIME_ROUTINE_CHAIN_STARTED   = 4,
    RUNTIME_ROUTINE_CHAIN_CANCELLED = 5,
    RUNTIME_ROUTINE_CHAIN_COMPLETED = 6,
};

enum runtime_work_queue_status : int
{
    RUNTIME_WORK_QUEUE_NOT_STARTED = 0,
    RUNTIME_WORK_QUEUE_STOPPED   = 1,
    RUNTIME_WORK_QUEUE_FAILED    = 2,
    RUNTIME_WORK_QUEUE_PAUSED    = 3,
    RUNTIME_WORK_QUEUE_STARTED   = 4,
    RUNTIME_WORK_QUEUE_CANCELLED = 5,
    RUNTIME_WORK_QUEUE_COMPLETED = 6,
};

enum runtime_work_run_result : int
{
	RUNTIME_WORK_RUN_FAILED      = 0,
	RUNTIME_WORK_RUN_SUCCEEDED   = 1,
	RUNTIME_WORK_RUN_BYPASS      = 2
};

enum runtime_module_type : int
{
	RUNTIME_MAIN        = 0,
	RUNTIME_COMMANDLINE = RUNTIME_MAIN, //.we use main because we want the main thread to print console output.
	RUNTIME_NETWORKING  = 2,
	RUNTIME_PERSISTENCE = 3,
	RUNTIME_GAMELOGIC   = 4,
	RUNTIME_SCRIPTVM    = 5,
	RUNTIME_DATABASE    = RUNTIME_MAIN, // Database utilizes main thread instead of its own separate thread.
	RUNTIME_MODULE_MAX  = 7
};

enum runtime_synchronization_method : int
{
	RUNTIME_SYNC_NONE = 0,
	RUNTIME_SYNC_WAIT_NO_CHECK_STATE = 1,
	RUNTIME_SYNC_WAIT_CHECK_STATE = 2
};

class RuntimeContextChain;

enum runtime_context_result : int
{
	RUNTIME_CONTEXT_NO_STATE = 0,
	RUNTIME_CONTEXT_FAIL     = 1,
	RUNTIME_CONTEXT_PASS     = 2
};

enum runtime_context_state : int
{
	RUNTIME_CONTEXT_STATE_INACTIVE = 0,
	RUNTIME_CONTEXT_STATE_ACTIVE = 1,
	RUNTIME_CONTEXT_STATE_WAITING = 2
};
class SystemRoutineManager;

class RuntimeContext : public std::enable_shared_from_this<RuntimeContext>
{
public:
    RuntimeContext(SystemRoutineManager &hsr_manager, runtime_synchronization_method sync_t = RUNTIME_SYNC_NONE) 
	: _hsr_manager(hsr_manager), _synchronization_t(sync_t), _uuid(boost::uuids::random_generator()()), _queue_manager(_control_agent) 
	{ }

	class ResultContext
	{
	public:
		virtual bool has_result()
		{
			return true;
		}
	};

    class WorkContext
    {
    public:
        virtual bool execute() 
		{
			return true;
		}
    };

    class WorkControlAgent
    {
    public:
        bool start()
        {
            runtime_work_queue_status status = get_status();

            if (status > RUNTIME_WORK_QUEUE_NOT_STARTED)
                return false;

            _status.store(RUNTIME_WORK_QUEUE_STARTED);
            return true;
        }

        bool stop() 
        { 
            runtime_work_queue_status status = get_status();
            runtime_work_queue_status stop = RUNTIME_WORK_QUEUE_STOPPED; 

            if (status == RUNTIME_WORK_QUEUE_FAILED || status == RUNTIME_WORK_QUEUE_COMPLETED || status == stop)
                return false;

            _status.store(stop);

             return true;
        }

        bool pause() 
        {
            runtime_work_queue_status status = get_status();

            if (status == RUNTIME_WORK_QUEUE_FAILED || status == RUNTIME_WORK_QUEUE_COMPLETED)
                return false;

            _status.store(RUNTIME_WORK_QUEUE_PAUSED);
            return true;
        }

        bool cancel()
        {
            runtime_work_queue_status status = get_status();

            if (status == RUNTIME_WORK_QUEUE_CANCELLED || status == RUNTIME_WORK_QUEUE_COMPLETED)
                return false;

            _status.compare_exchange_strong(status, RUNTIME_WORK_QUEUE_CANCELLED);
            return true;
        }

		bool completed()
		{
			runtime_work_queue_status status = get_status();

			if (status == RUNTIME_WORK_QUEUE_COMPLETED)
				return false;
			
			_status.store(RUNTIME_WORK_QUEUE_COMPLETED);
			return true;
		}

		bool failed()
		{
			runtime_work_queue_status status = get_status();

			if (status == RUNTIME_WORK_QUEUE_FAILED)
				return false;

			_status.store(RUNTIME_WORK_QUEUE_FAILED);
			return true;
		}

        runtime_work_queue_status get_status() { return _status.load(); }

        std::atomic<enum runtime_work_queue_status> _status{RUNTIME_WORK_QUEUE_NOT_STARTED};
    };

    class WorkQueueManager
    {
    public:
        WorkQueueManager(WorkControlAgent &control_agent) : _control_agent(control_agent) { }

        void push(std::shared_ptr<WorkContext> seg) { _queue.push(std::move(seg)); }
        std::shared_ptr<WorkContext> pop() 
        {
            if (_queue.empty())
                return nullptr;

            std::shared_ptr<WorkContext> ret;
            _queue.pop(ret);
            return ret;
        }

        bool process()
        {
			std::shared_ptr<WorkContext> context = nullptr;
			
			//_control_agent.start();

			bool failed = false;

            while((context = pop()) != nullptr) {
				while (_control_agent.get_status() == RUNTIME_WORK_QUEUE_PAUSED || _control_agent.get_status() == RUNTIME_WORK_QUEUE_STOPPED) {
					if (!_paused)
						_paused = true;
				}

				if (_paused == true)
					_paused = false;

				if (_control_agent.get_status() == RUNTIME_WORK_QUEUE_CANCELLED) {
					return false;
				}

				// break on execution failure.
				if (context->execute() == false) {
					failed = true;
					break;
				}

            }

			if (failed == true) {
				_control_agent.failed();
				return false;
			}

			_control_agent.completed();

			return true;
        }

		bool is_paused() { return _paused; }
        WorkControlAgent &_control_agent;
        boost::lockfree::spsc_queue<std::shared_ptr<WorkContext>, boost::lockfree::capacity<100>> _queue;
		std::atomic<bool> _paused{false};
    };
	
	std::shared_ptr<WorkContext> pop() { return _queue_manager.pop(); }
	void push(std::shared_ptr<WorkContext> context) { _queue_manager.push(context); }
	
    virtual bool run() 
	{ 
		set_context_state(RUNTIME_CONTEXT_STATE_ACTIVE);

		if (_queue_manager.process()) {
			set_context_result(RUNTIME_CONTEXT_PASS);
			return true;
		}

		set_context_result(RUNTIME_CONTEXT_FAIL);
		return false;
	}

	WorkQueueManager &get_queue_manager() { return _queue_manager; }
	WorkControlAgent &get_control_agent() { return _control_agent; }

	SystemRoutineManager &get_routine_manager() { return _hsr_manager; }

	std::string get_uuid_string() { return boost::uuids::to_string(_uuid); }

	void set_context_result(runtime_context_result pass = RUNTIME_CONTEXT_NO_STATE)
	{
		_result = pass;
	}
	runtime_context_result get_context_result() { return _result.load(); }
	
	void set_context_state(runtime_context_state state = RUNTIME_CONTEXT_STATE_INACTIVE)
	{
		_context_state_t = state;
	}
	runtime_context_state get_context_state() { return _context_state_t.load(); }

	void set_synchronization_method(runtime_synchronization_method sync) { _synchronization_t = sync; }
	runtime_synchronization_method get_synchronization_method() { return _synchronization_t; }

	void dispatch();

protected:
	SystemRoutineManager &_hsr_manager;
	WorkControlAgent _control_agent;
	WorkQueueManager _queue_manager;
	boost::uuids::uuid _uuid;
	std::atomic<enum runtime_context_result> _result{RUNTIME_CONTEXT_NO_STATE};
	runtime_synchronization_method _synchronization_t{RUNTIME_SYNC_NONE};
	std::atomic<enum runtime_context_state> _context_state_t{RUNTIME_CONTEXT_STATE_INACTIVE};
};

template <typename T = int>
class ContextWithResult
{
public:
	virtual bool has_result() { return true; }
	virtual T get_result() { return _result; }
	virtual void set_result(T result) { _result = result; }

	virtual std::vector<T> get_result_vector() { return _result_vector; }
	virtual void set_result_vector(std::vector<T> result_vector) { _result_vector = result_vector; }

protected:
	T _result;
	std::vector<T> _result_vector;
};

template <typename T = int>
class ContextUsesResult
{
public:
	virtual bool has_use_result() { return true; }
	virtual T get_use_result() { return _result; }
	virtual void set_use_result(T result) { _result = result; }

	virtual std::vector<T> get_use_result_vector() { return _result_vector; }
	virtual void set_use_result_vector(std::vector<T> result_vector) { _result_vector = result_vector; }

protected:
	T _result;
	std::vector<T> _result_vector;
};

template <typename ContextResultType = int, typename ContextUseResultType = int>
class RuntimeRoutineContext 
: public ContextWithResult<ContextResultType>,
  public ContextUsesResult<ContextUseResultType>,
  public RuntimeContext
{
public:
	RuntimeRoutineContext(Server *s,  runtime_synchronization_method sync_t = RUNTIME_SYNC_NONE);
	RuntimeRoutineContext(std::shared_ptr<MainframeComponent> component, runtime_synchronization_method sync_t = RUNTIME_SYNC_NONE);
	RuntimeRoutineContext(SystemRoutineManager &hsr_manager, runtime_synchronization_method sync_t = RUNTIME_SYNC_NONE);

	// @TODO derive from base class that is used to pass result on line 425, 
	// - pass it so we can withdraw the result for the use result in the next context of the chain.
	// - similar to how Work derives from WorkContext
    template <typename PayloadType>
    class Result : public RuntimeContext::ResultContext
    {
    public:
        Result(PayloadType payload) 
		: _payload(payload) { }
        Result(std::vector<PayloadType> payload_vector) 
		: _payload_vector(payload_vector) { }

		PayloadType get_one() { return _payload; }
		void set_one(PayloadType &payload) { _payload = payload; }

		std::vector<PayloadType> get_many() { return _payload_vector; }
		void set_many(std::vector<PayloadType> vec) { _payload_vector = vec; }

    	PayloadType _payload;
		std::vector<PayloadType> _payload_vector;
    };

    template <typename ParentContextType, typename RequestType = int, typename ResultType = int, typename UseResultType = int>
    class Work : public RuntimeContext::WorkContext
    {
    public:
        Work(std::shared_ptr<ParentContextType> parent_context, RequestType request) 
        : _parent_context(parent_context), _request(request) { }
        Work(std::shared_ptr<ParentContextType> parent_context, RequestType request, std::shared_ptr<Result<UseResultType>> use_result) 
        : _parent_context(parent_context), _request(request), _use_result(use_result) { }
        
		void set_request(RequestType request) { _request = request; }
		RequestType &get_request() { return _request; }

        void set_result(std::shared_ptr<Result<ResultType>> result) { _result = result; }
        std::shared_ptr<Result<ResultType>> get_result() { return _result; }
		bool has_result() { return _result != nullptr; }

        virtual bool execute() 
        {
            std::cerr << "Nothing to execute." << std::endl;
			return true;
        }

		std::shared_ptr<ParentContextType> get_parent_context() { return _parent_context; }
		void set_parent_context(std::shared_ptr<ParentContextType> parent_context) { _parent_context = parent_context; }
		
        std::shared_ptr<Result<ResultType>> _result;
		std::shared_ptr<Result<UseResultType>> _use_result;
        RequestType _request;
		std::shared_ptr<ParentContextType> _parent_context;
    };

	template <typename ParentContextType>
	void prepare(std::shared_ptr<ParentContextType> parent_context)
	{
		this->set_use_result(parent_context->get_result());
		this->set_use_result_vector(parent_context->get_result_vector());
	}
};

class RuntimeContextChain : public std::enable_shared_from_this<RuntimeContextChain>
{
public:
    RuntimeContextChain(runtime_module_type run_module) 
	: _module_t(run_module), _uuid(boost::uuids::random_generator()()), _queue_manager(_control_agent, this) 
	{ }

    class ContextControlAgent
    {
    public:
        bool start()
        {
            runtime_routine_chain_status status = get_status();

            if (status > RUNTIME_ROUTINE_CHAIN_NOT_STARTED)
                return false;

            _status.store(RUNTIME_ROUTINE_CHAIN_STARTED);
            return true;
        }

        bool stop() 
        { 
            runtime_routine_chain_status status = get_status();
            runtime_routine_chain_status stop = RUNTIME_ROUTINE_CHAIN_STOPPED; 

            if (status == RUNTIME_ROUTINE_CHAIN_FAILED || status == RUNTIME_ROUTINE_CHAIN_COMPLETED || status == stop)
                return false;

            _status.store(stop);

             return true;
        }

        bool pause() 
        {
            runtime_routine_chain_status status = get_status();

            if (status == RUNTIME_ROUTINE_CHAIN_FAILED || status == RUNTIME_ROUTINE_CHAIN_COMPLETED)
                return false;

            _status.store(RUNTIME_ROUTINE_CHAIN_PAUSED);
            return true;
        }

        bool cancel()
        {
            runtime_routine_chain_status status = get_status();

            if (status == RUNTIME_ROUTINE_CHAIN_CANCELLED || status <= RUNTIME_ROUTINE_CHAIN_STARTED)
                return false;

            _status.store(RUNTIME_ROUTINE_CHAIN_CANCELLED);
            return true;
        }

		bool completed()
		{
			runtime_routine_chain_status status = get_status();

			if (status == RUNTIME_ROUTINE_CHAIN_COMPLETED)
				return false;
			
			_status.store(RUNTIME_ROUTINE_CHAIN_COMPLETED);
			return true;
		}

		bool failed()
		{
			runtime_routine_chain_status status = get_status();

			if (status == RUNTIME_ROUTINE_CHAIN_FAILED)
				return false;

			_status.store(RUNTIME_ROUTINE_CHAIN_FAILED);
			return true;
		}

        runtime_routine_chain_status get_status() { return _status.load(); }

        std::atomic<enum runtime_routine_chain_status> _status{RUNTIME_ROUTINE_CHAIN_NOT_STARTED};
    };

    class ContextQueueManager
    {
    public:
        ContextQueueManager(ContextControlAgent &control_agent, RuntimeContextChain *chain) : _control_agent(control_agent), _chain(chain) { }

        void push(std::shared_ptr<RuntimeContext> seg) { _queue.push(std::move(seg)); }
        std::shared_ptr<RuntimeContext> pop() 
        {
            if (_queue.empty())
                return nullptr;

            std::shared_ptr<RuntimeContext> ret;
            _queue.pop(ret);
            return ret;
        }

        bool process();

		bool is_paused() { return _paused; }
		
        ContextControlAgent &_control_agent;
		RuntimeContextChain *_chain;
        boost::lockfree::spsc_queue<std::shared_ptr<RuntimeContext>, boost::lockfree::capacity<100>> _queue;
		std::atomic<bool> _paused{false};
    };
	
	std::shared_ptr<RuntimeContext> pop() { return _queue_manager.pop(); }
	void push(std::shared_ptr<RuntimeContext> context) { _queue_manager.push(context); }
	bool process() { return _queue_manager.process(); }

	ContextQueueManager &get_queue_manager() { return _queue_manager; }
	ContextControlAgent &get_control_agent() { return _control_agent; }

	ContextQueueManager _queue_manager;
    ContextControlAgent _control_agent;

	runtime_module_type get_module_type() { return _module_t; }
	void set_module_type(runtime_module_type module_t) { _module_t = module_t; }

	std::string get_uuid_string() { return boost::uuids::to_string(_uuid); }

private:
	boost::uuids::uuid _uuid;
	runtime_module_type _module_t;
};

class SystemRoutineManager
{
	struct runtime_map_data
	{
		runtime_module_type module_t;
		runtime_synchronization_method sync_t;
		std::shared_ptr<RuntimeContext> context;
		std::shared_ptr<RuntimeContextChain> context_chain;
	};

	typedef std::map<std::string, runtime_map_data> runtime_map;
public:
	SystemRoutineManager(runtime_module_type module_type)
	: _module_type(module_type)
	{
		if (_module_type < RUNTIME_MAIN || _module_type > Horizon::System::RUNTIME_SCRIPTVM) {
			std::cerr << "SystemRoutineManager for module type (" << module_type << ") failed to start. Invalid module type." << std::endl;
		}
	}

	virtual void register_(runtime_module_type module_t, runtime_synchronization_method sync_t, std::shared_ptr<RuntimeContext> context) 
	{
		runtime_map_data data = { module_t, sync_t, context, nullptr };
		_runtime_map.emplace(context->get_uuid_string(), data);
	}

	virtual void register_(runtime_module_type module_t, runtime_synchronization_method sync_t, std::shared_ptr<RuntimeContextChain> context_chain) 
	{
		runtime_map_data data = { module_t, sync_t, nullptr, context_chain };
		_runtime_map.emplace(context_chain->get_uuid_string(), data);
	}

	virtual std::shared_ptr<const runtime_map_data> find_runtime(std::string name)
	{
		auto it = _runtime_map.find(name);
		return (it != _runtime_map.end()) ? std::make_shared<const runtime_map_data>(it->second) : nullptr;
	}

	virtual int get_runtime_routine_count() 
	{
		return _runtime_map.size();
	}

	runtime_module_type get_module_type() { return _module_type; }

    void push(std::shared_ptr<RuntimeContextChain> chain) { 
		register_(chain->get_module_type(), RUNTIME_SYNC_NONE, chain);
		_system_queue_chain.push(std::move(chain)); 
	}
    void push(std::shared_ptr<RuntimeContext> seg) { 
		register_(get_module_type(), seg->get_synchronization_method(), seg);
		_system_queue.push(std::move(seg)); 
	}

    std::shared_ptr<RuntimeContext> pop() 
    {
		if (_system_queue.empty())
			return nullptr;

        std::shared_ptr<RuntimeContext> ret;
        _system_queue.pop(ret);
        return ret;
    }
	
    std::shared_ptr<RuntimeContextChain> pop_chain() 
    {   
        if (_system_queue_chain.empty())
            return nullptr;

        std::shared_ptr<RuntimeContextChain> ret;
        _system_queue_chain.pop(ret);
        return ret;
    }
	
	// Processes routine queue on every component and executes routine when available.
	// Call will be executed when the routine is within the system queue and has been popped out.
	// After addressing singlular system routines, it will execute the chain of routines. Both cannot happen together.
    void process_queue()
    {
        while(_system_queue.empty() == false) {
    	    std::shared_ptr<RuntimeContext> context = pop();
			if (context != nullptr)
	            context->run();
        }
		
        while(_system_queue_chain.empty() == false) {
    	    std::shared_ptr<RuntimeContextChain> routine_chain = pop_chain();
			if (routine_chain != nullptr)
	            routine_chain->get_queue_manager().process();
        }
    }

	boost::lockfree::spsc_queue<std::shared_ptr<RuntimeContext>, boost::lockfree::capacity<100>> _system_queue;
	boost::lockfree::spsc_queue<std::shared_ptr<RuntimeContextChain>, boost::lockfree::capacity<100>> _system_queue_chain;

private:
	runtime_map _runtime_map;
	runtime_module_type _module_type;
};
}
}

#endif /* HORIZON_SYSTEM_ROUTINES_HPP */