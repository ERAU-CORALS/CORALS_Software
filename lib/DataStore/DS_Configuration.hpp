/**
 ********************************************************************************
 * @file    DS_Configuration.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Configuration for Arduino StateManager
 * @version 1.0
 * @date    2024-03-20
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __DS_CONFIGURATION_HPP__
#define __DS_CONFIGURATION_HPP__

#include "Configuration.hpp"

#define DS_OUT SERIAL_OUT
const String DS_NAME = CORE_NAME + " StateManager";

#if !defined(DS_DEBUG) || DS_DEBUG > 1
    #ifdef DS_DEBUG
        #undef DS_DEBUG
    #endif
    #define DS_DEBUG DEBUG
#endif

#define DS_OUT_PRINT(x) DS_OUT.print(DS_NAME + ": " + x)
#define DS_OUT_PRINTLN(x) DS_OUT_PRINT(x + "\n")

#define DS_DEBUG_PRINT(x) if(DS_DEBUG) DS_OUT.print(DS_NAME + " DEBUG: " + x)
#define DS_DEBUG_PRINTLN(x) DS_DEBUG_PRINT(x + "\n")

#endif // __DS_CONFIGURATION_HPP__