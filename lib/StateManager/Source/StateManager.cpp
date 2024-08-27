/**
 ********************************************************************************
 * @file    StateManager.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   State Manager for CORALS Processes
 * @version 1.0
 * @date    2024-03-20
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "StateManager.hpp"

#include <List.tpp>

#include "SM_Configuration.hpp"
#include "SM_Types.hpp"
#include "StateManager_Process.hpp"

namespace StateManager {

StateManager::StateManager() {}
StateManager::~StateManager() {}

void StateManager::Register(const char *name, 
                            SM_Function_t function, 
                            SM_Time period_ms, 
                            SM_Priority priority) {
    SMFunction new_function = {
        .name = name,
        .function = function,
        .priority = priority,
        .period_ms = period_ms,
        .last_call = 0
    };

    functions.push_back(new_function);

    SM_DEBUG.print("Registered Function: ");
    SM_DEBUG.println(name);
    SM_DEBUG.print("\tPeriod: ");
    SM_DEBUG.print(period_ms);
    SM_DEBUG.println("ms");
    SM_DEBUG.print("\tPriority: ");
    SM_DEBUG.println((int)priority);
}

void StateManager::Register(const char *name, 
                            Process* process, 
                            SM_Time period_ms, 
                            SM_Priority priority) {
    SMProcess new_process = {
        .name = name,
        .process = process,
        .priority = priority,
        .period_ms = period_ms,
        .last_call = 0
    };

    processes.push_back(new_process);

    SM_DEBUG.print("Registered Process: ");
    SM_DEBUG.println(name);
    SM_DEBUG.print("\tPeriod: ");
    SM_DEBUG.print(period_ms);
    SM_DEBUG.println("ms");
    SM_DEBUG.print("\tPriority: ");
    SM_DEBUG.println((int)priority);
}

void StateManager::Run() {
    if (functions.size() == 0 && processes.size() == 0) return;

    SM_DEBUG.print("Iterating through ");
    SM_DEBUG.print(functions.size());
    SM_DEBUG.println(" functions...");

    SM_WeightedPriority max_function_priority = 0;
    ListSize max_function_priority_index = 0;
    for (ListSize i = 0; i < functions.size(); i++) {
        SM_WeightedPriority priority = DetermineWeightedFunctionPriority(i);
        if (priority > max_function_priority) {
            max_function_priority = priority;
            max_function_priority_index = i;
        }
    }

    SM_DEBUG.print("Iterating through ");
    SM_DEBUG.print(processes.size());
    SM_DEBUG.println(" processes...");
        
    SM_WeightedPriority max_process_priority = 0;
    ListSize max_process_priority_index = 0;
    for (ListSize i = 0; i < processes.size(); i++) {
        SM_WeightedPriority priority = DetermineWeightedProcessPriority(i);
        if (priority > max_process_priority) {
            max_process_priority = priority;
            max_process_priority_index = i;
        }
    }

    if (max_function_priority == 0 && max_process_priority == 0) return;
        
    if (max_function_priority > max_process_priority) {
        CallFunction(max_function_priority_index);
    }
    else {
        CallProcess(max_process_priority_index);
    }
}

SM_WeightedPriority StateManager::DetermineWeightedFunctionPriority(ListSize f_index) {
    SMFunction &function = functions[f_index];
    SM_Time delay_time = millis() - function.last_call;
    SM_Time delta_time = (delay_time > function.period_ms) ? delay_time - function.period_ms : 0;
    SM_WeightedPriority weighted_priority = (SM_WeightedPriority)function.priority * delta_time;

    SM_DEBUG.print(function.name);
    SM_DEBUG.print(": ");
    SM_DEBUG.print(delta_time);
    SM_DEBUG.print("ms, ");
    SM_DEBUG.println(weighted_priority);

    return weighted_priority;
}

SM_WeightedPriority StateManager::DetermineWeightedProcessPriority(ListSize p_index) {
    SMProcess &process = processes[p_index];
    SM_Time delay_time = millis() - process.last_call;
    SM_Time delta_time = (delay_time > process.period_ms) ? delay_time - process.period_ms : 0;
    SM_WeightedPriority weighted_priority = (SM_WeightedPriority)process.priority * delta_time;
        
    SM_DEBUG.print(process.name);
    SM_DEBUG.print(": ");
    SM_DEBUG.print(delta_time);
    SM_DEBUG.print("ms, ");
    SM_DEBUG.println(weighted_priority);
        
    return weighted_priority;
}

void StateManager::CallFunction(ListSize f_index) {
    SM_DEBUG.print("CALLING FUNCTION: ");
    SM_DEBUG.println(functions[f_index].name);
    functions[f_index].last_call = millis();
    functions[f_index].function();
}

void StateManager::CallProcess(ListSize p_index) {
    SM_DEBUG.print("CALLING PROCESS: ");
    SM_DEBUG.println(processes[p_index].name);
    processes[p_index].last_call = millis();
    processes[p_index].process->Run();
}

} // end namespace StateManager