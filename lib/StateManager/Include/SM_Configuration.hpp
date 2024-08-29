/**
 ********************************************************************************
 * @file    SM_Configuration.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Configuration for Arduino StateManager
 * @version 1.0
 * @date    2024-03-20
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __SM_CONFIGURATION_HPP__
#define __SM_CONFIGURATION_HPP__

#include "Configuration.hpp"

#define SM_OUT SERIAL_OUT
const String SM_NAME = CORE_NAME + " StateManager";

#if !defined(SM_DEBUG) || SM_DEBUG > 1
    #ifdef SM_DEBUG
        #undef SM_DEBUG
    #endif
    #define SM_DEBUG DEBUG
#endif

#define SM_OUT_PRINT(x) SM_OUT.print(SM_NAME + ": " + x)
#define SM_OUT_PRINTLN(x) SM_OUT_PRINT(x + "\n")

#define SM_DEBUG_PRINT(x) if(SM_DEBUG) SM_OUT.print(SM_NAME + " DEBUG: " + x)
#define SM_DEBUG_PRINTLN(x) SM_DEBUG_PRINT(x + "\n")

#endif // __SM_CONFIGURATION_HPP__