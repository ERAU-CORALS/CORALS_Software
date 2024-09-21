/**
 ********************************************************************************
 * @file    StateManager_Types.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   State Manager Types for CORALS Processes
 * @version 1.0
 * @date    2024-03-22
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __STATEMANAGER_TYPES_HPP__
#define __STATEMANAGER_TYPES_HPP__

namespace StateManager {

typedef void (*SM_Function_t)();

using SM_Time = unsigned long;
using SM_WeightedPriority = unsigned long; 

enum class SM_Priority {
    PRIORITY_LOWEST = 1,
    PRIORITY_LOW,
    PRIORITY_MEDIUM,
    PRIORITY_HIGH,
    PRIORITY_HIGHEST
};

} // end namespace StateManager

#endif // __STATEMANAGER_TYPES_HPP__