/**
 ********************************************************************************
 * @file    StateManager_Configuration.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Configuration for Arduino MEGA 2560
 * @version 1.0
 * @date    2024-03-20
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __STATEMANAGER_CONFIGURATION_HPP__
#define __STATEMANAGER_CONFIGURATION_HPP__

#include <Arduino.h>
#include "CORALS_Configuration.hpp"

// Serial USART Allocation
#define SM_DEBUG DEBUG_OUT
const String SM_NAME = "StateManager";

#define SM_DEBUG_PRINT(x) if (DEBUG) SM_DEBUG_PRINT(SM_NAME + ": " + x)
#define SM_DEBUG_PRINTLN(x) SM_DEBUG_PRINT(x + "\n")

#endif // __STATEMANAGER_CONFIGURATION_HPP__