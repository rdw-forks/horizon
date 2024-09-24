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
 * This is proprietary software. Unauthorized copying,
 * distribution, or modification of this file, via any
 * medium, is strictly prohibited. All rights reserved.
 **************************************************/

#include "System.hpp"
#include "Server.hpp"

Horizon::System::RuntimeRoutineContext::RuntimeRoutineContext(Server *s, runtime_synchronization_method sync_t) 
: Horizon::System::RuntimeContext(s->get_system_routine_manager(), sync_t) 
{ 
} 

Horizon::System::RuntimeRoutineContext::RuntimeRoutineContext(std::shared_ptr<KernelComponent> component, runtime_synchronization_method sync_t) 
: Horizon::System::RuntimeContext(component->get_system_routine_manager(), sync_t)
{ 
} 

Horizon::System::RuntimeRoutineContext::RuntimeRoutineContext(SystemRoutineManager &hsr_manager, runtime_synchronization_method sync_t)
: Horizon::System::RuntimeContext(hsr_manager, sync_t)
{
}
	
void Horizon::System::RuntimeContext::dispatch() { _hsr_manager.push(shared_from_this()); }

bool Horizon::System::RuntimeContextChain::ContextQueueManager::process()
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

		if (context->get_routine_manager().get_module_type() != _chain->get_module_type()) {
			context->dispatch();

			if (context->get_synchronization_method() == RUNTIME_SYNC_WAIT_NO_CHECK_STATE) {
				while(context->get_context_result() == RUNTIME_CONTEXT_NO_STATE) {
					if (context->get_context_state() != RUNTIME_CONTEXT_STATE_WAITING) {
						context->set_context_state(RUNTIME_CONTEXT_STATE_WAITING);
					}
				}

				if (context->get_context_state() == RUNTIME_CONTEXT_STATE_WAITING) {
					context->set_context_state(RUNTIME_CONTEXT_STATE_ACTIVE);
				}
				/* Don't check the pass or fail of the context. */
			} else if (context->get_synchronization_method() == RUNTIME_SYNC_WAIT_CHECK_STATE) {
				while(context->get_context_result() == RUNTIME_CONTEXT_NO_STATE) {
					if (context->get_context_state() != RUNTIME_CONTEXT_STATE_WAITING) {
						context->set_context_state(RUNTIME_CONTEXT_STATE_WAITING);
					}
				}
				if (context->get_context_state() == RUNTIME_CONTEXT_STATE_WAITING) {
					context->set_context_state(RUNTIME_CONTEXT_STATE_ACTIVE);
				}
				/* check context result whether pass or fail. */
				if (context->get_context_result() == RUNTIME_CONTEXT_FAIL) {
					failed = true;
					break;
				}
			}

		} else if (context->run() == false) {
			failed = true;
			break;
		}
    }

	_queue.reset();

	if (failed == true) {
		_control_agent.failed();
		return false;
	}

	_control_agent.completed();

	return true;
}