/**
 ********************************************************************************
 * @file    StateManager_Process.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   State Manager for CORALS Processes
 * @version 1.0
 * @date    2024-03-22
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "StateManager_Process.hpp"

#include <List.tpp>

#include "SM_Configuration.hpp"
#include "SM_Types.hpp"

namespace StateManager {
Process::Process() : index(0) {};
Process::~Process() {};

void Process::Register(const char *name, SM_Function_t function) { 
    Function new_function = {
        .name = name,
        .function = function
    };
    functions.push_back(new_function);
    
    SM_DEBUG.print("Registered Function to Process: ");
    SM_DEBUG.println(name);
};

void Process::Run() {
    if (functions.size() == 0) return;
    
    functions[index].function();
    index++;
    index %= functions.size();
}

} // end namespace StateManager