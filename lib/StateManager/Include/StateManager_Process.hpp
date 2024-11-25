/**
 ********************************************************************************
 * @file    StateManager_Process.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   State Manager for CORALS Processes
 * @version 1.0
 * @date    2024-03-22
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __STATEMANAGER_PROCESS_HPP__
#define __STATEMANAGER_PROCESS_HPP__

#include <List.tpp>

#include "SM_Configuration.hpp"
#include "SM_Types.hpp"

namespace StateManager {

class Process {

    struct Function {
        const char *name;
        SM_Function_t function;
    };

    using FunctionList = DataStructures::List::List<Function>;
    using ListSize = DataStructures::List::ListSize_t;

    public:
        Process();
        ~Process();

        void Register(const char *name, SM_Function_t function);
        void Run();
    
    private:
        FunctionList functions;
        ListSize index;

};

} // end namespace StateManager

#endif // __STATEMANAGER_PROCESS_HPP__