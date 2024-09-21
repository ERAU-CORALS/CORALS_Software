/**
 ********************************************************************************
 * @file    StateManager.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   State Manager for CORALS Processes
 * @version 1.0
 * @date    2024-03-20
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __STATE_MANAGER_HPP__
#define __STATE_MANAGER_HPP__

#include <List.tpp>

#include "SM_Configuration.hpp"
#include "SM_Types.hpp"
#include "StateManager_Process.hpp"

#define S_TO_MS(s) (s * 1000)

namespace StateManager {
    
class StateManager {

    struct SMFunction {
        const char *name;
        SM_Function_t function;
        SM_Priority priority;
        SM_Time period_ms;
        SM_Time last_call;
    };
    struct SMProcess {
        const char *name;
        Process* process;
        SM_Priority priority;
        SM_Time period_ms;
        SM_Time last_call;
    };

    using FunctionList = DataStructures::List::List<SMFunction>;
    using ProcessList = DataStructures::List::List<SMProcess>;
    using ListSize = DataStructures::List::ListSize_t;

public:
    StateManager();
    ~StateManager();

    void Register(const char *name, 
                  SM_Function_t function, 
                  SM_Time period_ms, 
                  SM_Priority priority = SM_Priority::PRIORITY_MEDIUM);

    void Register(const char *name, 
                  Process* process, 
                  SM_Time period_ms, 
                  SM_Priority priority = SM_Priority::PRIORITY_MEDIUM);

    void Run();

private:

    FunctionList functions;
    ProcessList processes;

    SM_WeightedPriority DetermineWeightedFunctionPriority(ListSize f_index);
    SM_WeightedPriority DetermineWeightedProcessPriority(ListSize p_index);

    void CallFunction(ListSize f_index);
    void CallProcess(ListSize p_index);

};

} // end namespace CORALS

#endif  // __STATE_MANAGER_HPP__