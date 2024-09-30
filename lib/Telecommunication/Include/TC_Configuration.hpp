/**
 ********************************************************************************
 * @file    TC_Configuration.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Configuration for Telecommunication Module
 * @version 1.0
 * @date    2024-03-20
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __TC_CONFIGURATION_HPP__
#define __TC_CONFIGURATION_HPP__

#include "Configuration.hpp"

#define TC_OUT SERIAL_OUT
const String TC_NAME = CORE_NAME + " Telecommunication";

#if !defined(TC_DEBUG) || TC_DEBUG > 1
    #ifdef TC_DEBUG
        #undef TC_DEBUG
    #endif
    #define TC_DEBUG DEBUG
#endif

#define TC_OUT_PRINT(x) TC_OUT.print(TC_NAME + ": " + x)
#define TC_OUT_PRINTLN(x) TC_OUT_PRINT(x + "\n")

#define TC_DEBUG_PRINT(x) if(TC_DEBUG) TC_OUT.print(TC_NAME + " DEBUG: " + x)
#define TC_DEBUG_PRINTLN(x) TC_DEBUG_PRINT(x + "\n")

#endif // __TC_CONFIGURATION_HPP__