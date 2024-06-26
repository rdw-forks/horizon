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
#include "Core/Logging/Logger.hpp"
#include <optional>
#include <vector>
#include <memory>

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

enum runtime_dispatch_module_type : int
{
	RUNTIME_DISPATCH_MAIN        = 0,
	RUNTIME_DISPATCH_COMMANDLINE = 1,
	RUNTIME_DISPATCH_NETWORKING  = 2,
	RUNTIME_DISPATCH_PERSISTENCE = 3,
	RUNTIME_DISPATCH_GAMELOGIC   = 4,
	RUNTIME_DISPATCH_SCRIPTVM    = 5
};

enum runtime_synchronization_method : int
{
	RUNTIME_SYNC_NONE = 0,
	RUNTIME_SYNC_WAIT_NORETURN = 1,
	RUNTIME_SYNC_WAIT_RETURN = 2
};

class RuntimeContextChain;

class RuntimeContext : public std::enable_shared_from_this<RuntimeContext>
{
public:
    RuntimeContext() : _queue_manager(_control_agent) { }

    class WorkContext
    {
    public:
        virtual bool execute() 
		{ 
			HLog(warning) << "Nothing to execute";
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

            if (status == RUNTIME_WORK_QUEUE_CANCELLED || status <= RUNTIME_WORK_QUEUE_STARTED)
                return false;

            _status.store(RUNTIME_WORK_QUEUE_CANCELLED);
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
			
			_control_agent.start();

			bool failed = false;

            while((context = pop()) != nullptr) {
				while (_control_agent.get_status() == RUNTIME_WORK_QUEUE_PAUSED || _control_agent.get_status() == RUNTIME_WORK_QUEUE_STOPPED) {
					if (!_paused)
						_paused = true;
				}

				if (_paused == true)
					_paused = false;

				if (_control_agent.get_status() == RUNTIME_WORK_QUEUE_CANCELLED)
					return false;

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
		return _queue_manager.process();
	}

	WorkQueueManager &get_queue_manager() { return _queue_manager; }
	WorkControlAgent &get_control_agent() { return _control_agent; }

protected:
	WorkControlAgent _control_agent;
	WorkQueueManager _queue_manager;
};

class RuntimeRoutineContext : public RuntimeContext
{
public:
	// @TODO derive from base class that is used to pass result on line 425, 
	// - pass it so we can withdraw the result for the use result in the next context of the chain.
	// - similar to how Work derives from WorkContext
    template <typename PayloadType>
    class Result
    {
    public:
        Result(PayloadType payload) : _payload(payload) { }
        Result(std::vector<PayloadType> payload_vector) : _payload_vector(payload_vector) { }

		PayloadType get_one() { return _payload; }
		void set_one(PayloadType &payload) { _payload = payload; }

		std::vector<PayloadType> get_many() { return _payload_vector; }
		void set_many(std::vector<PayloadType> vec) { _payload_vector = vec; }
	private:
    	PayloadType _payload;
		std::vector<PayloadType> _payload_vector;
    };

    template <typename RequestType = int, typename ResultType = int, typename UseResultType = int>
    class Work : public RuntimeContext::WorkContext
    {
    public:
        Work(RequestType request, std::shared_ptr<RuntimeRoutineContext> context) 
        : _request(request), _context(context) { }
        Work(RequestType request, std::shared_ptr<RuntimeRoutineContext> context, std::shared_ptr<Result<UseResultType>> use_result) 
        : _request(request), _context(context), _use_result(use_result) { }
        
		void set_request(RequestType request) { _request = request; }
		RequestType &get_request() { return _request; }

        void set_result(std::shared_ptr<Result<ResultType>> result) { _result = result; }
        std::shared_ptr<Result<ResultType>> get_result() { return _result; }
		bool has_result() { return _result != nullptr; }

        virtual bool execute() 
        {
            set_result(std::make_shared<Result<UseResultType>>(_use_result->get_one() + 200));
            std::cerr << "Nothing to execute." << std::endl;
			return true;
        }
		
    private:
        std::shared_ptr<RuntimeRoutineContext> _context;
        std::shared_ptr<Result<ResultType>> _result;
		std::shared_ptr<Result<UseResultType>> _use_result;
        RequestType _request;
    };
};

class RuntimeContextChain
{
public:
    RuntimeContextChain() : _queue_manager(_control_agent) { }

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
        ContextQueueManager(ContextControlAgent &control_agent) : _control_agent(control_agent) { }

        void push(std::shared_ptr<RuntimeContext> seg) { _queue.push(std::move(seg)); }
        std::shared_ptr<RuntimeContext> pop() 
        {
            if (_queue.empty())
                return nullptr;

            std::shared_ptr<RuntimeContext> ret;
            _queue.pop(ret);
            return ret;
        }

        bool process()
        {
			std::shared_ptr<RuntimeContext> context = nullptr;
			
			_control_agent.start();

			bool failed = false;
            while((context = pop()) != nullptr) {
				while (_control_agent.get_status() == RUNTIME_ROUTINE_CHAIN_PAUSED || _control_agent.get_status() == RUNTIME_ROUTINE_CHAIN_STOPPED) {
					if (!_paused)
						_paused = true;
				}

				if (_paused == true)
					_paused = false;

				if (_control_agent.get_status() == RUNTIME_ROUTINE_CHAIN_CANCELLED)
					return false;

				if (context->run() == false) {
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
        ContextControlAgent &_control_agent;
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
};

class SystemRoutineManager
{
	struct runtime_map_data
	{
		runtime_dispatch_module_type module_t;
		runtime_synchronization_method sync_t;
		std::shared_ptr<RuntimeContext> context;
		std::shared_ptr<RuntimeContextChain> context_chain;
	};

	typedef std::map<std::string, runtime_map_data> runtime_map;
public:
	SystemRoutineManager(runtime_dispatch_module_type module_type)
	: _module_type(module_type)
	{
		if (_module_type < RUNTIME_DISPATCH_MAIN || _module_type > RUNTIME_DISPATCH_SCRIPTVM) {
			HLog(error) << "SystemRoutineManager for module type (" << module_type << ") failed to start. Invalid module type.";
		}
	}

	virtual void register_(runtime_dispatch_module_type module_t, runtime_synchronization_method sync_t, std::shared_ptr<RuntimeContext> context) 
	{
		runtime_map_data data = { module_t, sync_t, context, nullptr };
		_runtime_map.emplace(typeid(context).name(), data);
	}

	virtual void register_(runtime_dispatch_module_type module_t, runtime_synchronization_method sync_t, std::shared_ptr<RuntimeContextChain> context_chain) 
	{
		runtime_map_data data = { module_t, sync_t, nullptr, context_chain };
		_runtime_map.emplace(typeid(context_chain).name(), data);
	}

	virtual std::shared_ptr<const runtime_map_data> find_runtime(std::string name)
	{
		auto it = _runtime_map.find(name);
		return (it != _runtime_map.end()) ? std::make_shared<const runtime_map_data>(it->second) : nullptr;
	}

    void push(std::shared_ptr<RuntimeContextChain> chain) { _system_queue_chain.push(std::move(chain)); }
    void push(std::shared_ptr<RuntimeContext> seg) { _system_queue.push(std::move(seg)); }

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
			if (find_runtime(typeid(context).name()) == nullptr) {
				HLog(warning) << "HSR: Tried to run a routine that is not registered. (Name: " << typeid(context).name() << ") skipping...";
				continue;
			}
			if (context != nullptr)
	            context->run();
        }
		
        while(_system_queue_chain.empty() == false) {
    	    std::shared_ptr<RuntimeContextChain> routine_chain = pop_chain();
			if (find_runtime(typeid(routine_chain).name()) == nullptr) {
				HLog(warning) << "HSR: Tried to run a routine chain that is not registered. (Name: " << typeid(routine_chain).name() << ") skipping...";
				continue;
			}
			if (routine_chain != nullptr)
	            routine_chain->get_queue_manager().process();
        }
    }

	boost::lockfree::spsc_queue<std::shared_ptr<RuntimeContext>, boost::lockfree::capacity<100>> _system_queue;
	boost::lockfree::spsc_queue<std::shared_ptr<RuntimeContextChain>, boost::lockfree::capacity<100>> _system_queue_chain;

private:
	runtime_map _runtime_map;
	runtime_dispatch_module_type _module_type;
};
}
}

#endif /* HORIZON_SYSTEM_ROUTINES_HPP */