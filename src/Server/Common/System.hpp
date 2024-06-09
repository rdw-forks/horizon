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

enum runtime_work_segment_result_type : int
{
	RUNTIME_WORK_SEGMENT_RESULT_NONE = 0,
	RUNTIME_WORK_SEGMENT_RESULT_ONE  = 1,
	RUNTIME_WORK_SEGMENT_RESULT_MANY = 2,
	RUNTIME_WORK_SEGMENT_RESULT_NULL = 3
};

enum runtime_work_segment_return_type : int
{
	RUNTIME_WORK_RETURN_HAS_NONE       = 0,
	RUNTIME_WORK_RETURN_HAS_ONE        = 1,
	RUNTIME_WORK_RETURN_HAS_MANY       = 2
};

class RuntimeWorkSegment
{
public: 
    RuntimeWorkSegment(runtime_work_segment_return_type return_type) 
    : _return_type(return_type) { }

	runtime_work_segment_return_type get_return_type() { return _return_type; }

    int get_priority() { return _priority; }
    void set_priority(int priority) { _priority = priority; }

    int get_stage() { return _stage; }
    void set_stage(int stage) { _stage = stage; }

private:
    int _priority{0};
    int _stage{0};
	runtime_work_segment_return_type _return_type{RUNTIME_WORK_RETURN_HAS_NONE};
};

class RuntimeContext
{
public:
    class WorkContext
    {
    public:
        virtual void execute() { HLog(warning) << "Nothing to execute"; }
    };
    virtual void run() { HLog(warning) << "Nothing to execute."; }
};

class RuntimeRoutineContext : public RuntimeContext
{
public:
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

        virtual void execute() 
        {
            set_result(std::make_shared<Result<UseResultType>>(_use_result->get_one() + 200));
            std::cerr << "Nothing to execute." << std::endl;
        }
		
    private:
        std::shared_ptr<RuntimeRoutineContext> _context;
        std::shared_ptr<Result<ResultType>> _result;
		std::shared_ptr<Result<UseResultType>> _use_result;
        RequestType _request;
    };

    void add_work(std::shared_ptr<WorkContext> work) { _work.push_back(work); }

    void run() override 
    { 
        if (_work.size() == 0) { 
            HLog(error) << "There is no work.";
            return;
        }

        for (auto work : _work)
            work->execute(); 
    }

    // Simplify the architecture of the concept design
    std::vector<std::shared_ptr<WorkContext>> _work;
};

class RuntimeRoutineContextChain
{
public:
    RuntimeRoutineContextChain() : _queue_manager(_control_agent) { }

    class SegmentControlAgent
    {
    public:
        bool start()
        {
            runtime_routine_chain_status status = _status.load();

            if (status > RUNTIME_ROUTINE_CHAIN_NOT_STARTED)
                return false;

            _status.store(RUNTIME_ROUTINE_CHAIN_STARTED);
            return true;
        }

        bool stop() 
        { 
            runtime_routine_chain_status status = _status.load();
            runtime_routine_chain_status stop = RUNTIME_ROUTINE_CHAIN_STOPPED; 

            if (status == RUNTIME_ROUTINE_CHAIN_FAILED || status == RUNTIME_ROUTINE_CHAIN_COMPLETED || status == stop)
                return false;

            _status.store(stop);

             return true;
        }

        bool pause() 
        {
            runtime_routine_chain_status status = _status.load();

            if (status == RUNTIME_ROUTINE_CHAIN_FAILED || status == RUNTIME_ROUTINE_CHAIN_COMPLETED)
                return false;

            _status.store(RUNTIME_ROUTINE_CHAIN_PAUSED);
            return true;
        }

        bool cancel()
        {
            runtime_routine_chain_status status = _status.load();

            if (status == RUNTIME_ROUTINE_CHAIN_FAILED || status <= RUNTIME_ROUTINE_CHAIN_STARTED)
                return false;

            _status.store(RUNTIME_ROUTINE_CHAIN_CANCELLED);
            return true;
        }

        bool restart()
        {
            runtime_routine_chain_status status = _status.load();

            if (status == RUNTIME_ROUTINE_CHAIN_COMPLETED || status == RUNTIME_ROUTINE_CHAIN_STARTED)
                return false;
            
            return true;
        }

        runtime_routine_chain_status get_status() { return _status.load(); }

        std::atomic<enum runtime_routine_chain_status> _status{RUNTIME_ROUTINE_CHAIN_NOT_STARTED};
    };

    class SegmentQueueManager
    {
    public:
        SegmentQueueManager(SegmentControlAgent &control_agent) : _control_agent(control_agent) { }

        void push(std::shared_ptr<RuntimeRoutineContext> seg) { _queue.push(std::move(seg)); }
        std::shared_ptr<RuntimeRoutineContext> pop() 
        {
            runtime_routine_chain_status status = _control_agent.get_status();
            
            if (status == RUNTIME_ROUTINE_CHAIN_STOPPED || status == RUNTIME_ROUTINE_CHAIN_PAUSED)
                return nullptr;

            if (_queue.empty())
                return nullptr;

            std::shared_ptr<RuntimeRoutineContext> ret;
            _queue.pop(ret);
            return ret;
        }

        void process()
        {
			std::shared_ptr<RuntimeRoutineContext> context = nullptr;
			
            while((context = pop()) != nullptr) {
				context->run();
            }
        }

        SegmentControlAgent &_control_agent;
        boost::lockfree::spsc_queue<std::shared_ptr<RuntimeRoutineContext>, boost::lockfree::capacity<100>> _queue;
    };
	
	std::shared_ptr<RuntimeRoutineContext> pop() { return _queue_manager.pop(); }
	void push(std::shared_ptr<RuntimeRoutineContext> context) { _queue_manager.push(context); }
	void process() { _queue_manager.process(); }

	SegmentQueueManager &get_queue_manager() { return _queue_manager; }

	SegmentQueueManager _queue_manager;
    SegmentControlAgent _control_agent;
};

class SystemRoutineManager
{
public:
    void push(std::shared_ptr<RuntimeRoutineContextChain> chain) { _system_queue_chain.push(std::move(chain)); }
    void push(std::shared_ptr<RuntimeRoutineContext> seg) { _system_queue.push(std::move(seg)); }

    std::shared_ptr<RuntimeRoutineContext> pop() 
    {
		if (_system_queue.empty())
			return nullptr;

        std::shared_ptr<RuntimeRoutineContext> ret;
        _system_queue.pop(ret);
        return ret;
    }
	
    std::shared_ptr<RuntimeRoutineContextChain> pop_chain() 
    {   
        if (_system_queue_chain.empty())
            return nullptr;

        std::shared_ptr<RuntimeRoutineContextChain> ret;
        _system_queue_chain.pop(ret);
        return ret;
    }
	
	// Processes routine queue on every component and executes routine when available.
	// Call will be executed when the routine is within the system queue and has been popped out.
	// After addressing singlular system routines, it will execute the chain of routines. Both cannot happen together.
    void process_queue()
    {
        while(_system_queue.empty() == false) {
    	    std::shared_ptr<RuntimeRoutineContext> context = pop();
			if (context != nullptr)
	            context->run();
        }
		
        while(_system_queue_chain.empty() == false) {
    	    std::shared_ptr<RuntimeRoutineContextChain> routine_chain = pop_chain();
			if (routine_chain != nullptr)
	            routine_chain->get_queue_manager().process();
        }
    }

	boost::lockfree::spsc_queue<std::shared_ptr<RuntimeRoutineContext>, boost::lockfree::capacity<100>> _system_queue;
	boost::lockfree::spsc_queue<std::shared_ptr<RuntimeRoutineContextChain>, boost::lockfree::capacity<100>> _system_queue_chain;
};
}
}

#endif /* HORIZON_SYSTEM_ROUTINES_HPP */