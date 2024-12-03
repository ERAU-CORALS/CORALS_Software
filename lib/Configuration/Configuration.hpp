/**
 ********************************************************************************
 * @file    Configuration.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Master Configuration File
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __CONFIGURATION_HPP__
#define __CONFIGURATION_HPP__

#include <Arduino.h>
#include <SerialRPC.h>

#if !defined(DEBUG) || DEBUG > 1
    #ifdef DEBUG
        #undef DEBUG
    #endif
    #define DEBUG 0
#endif

#ifndef packed 
    #define packed // __attribute__((__packed__))
#endif

#if defined(CORE_CM4) && !defined(GIGA_R1_M4)
    #warning "GIGA_R1_M4 not defined in environment. Defining GIGA_R1_M4..."
    #define GIGA_R1_M4
#endif
#if defined(CORE_CM7) && !defined(GIGA_R1_M7)
    #warning "GIGA_R1_M7 not defined in environment. Defining GIGA_R1_M7..."
    #define GIGA_R1_M7
#endif

#if defined(GIGA_R1_M4) && defined(GIGA_R1_M7)
    #error "Dual Core compilation not allowed."
#endif

#if !defined(GIGA_R1_M4) && !defined(GIGA_R1_M7)
    #error "Environment variables incorrect. One Core must be defined."
#endif

#ifdef DEBUG_OUT
    #undef DEBUG_OUT
#endif

#ifdef GIGA_R1_M4

    #define SERIAL_OUT SerialRPC
    const String CORE_NAME = "CM4";

#endif

#ifdef GIGA_R1_M7

    #define SERIAL_OUT Serial
    const String CORE_NAME = "CM7";

#endif

#ifdef DEBUG_OUT_PRINT
    #undef DEBUG_OUT_PRINT
#endif
#ifdef DEBUG_OUT_PRINTLN
    #undef DEBUG_OUT_PRINTLN
#endif

#define SERIAL_OUT_PRINT(x) SERIAL_OUT.print(CORE_NAME + ": " + x)
#define SERIAL_OUT_PRINTLN(x) SERIAL_OUT_PRINT(x + "\n")

#define DEBUG_OUT_PRINT(x) if(DEBUG) SERIAL_OUT_PRINT(CORE_NAME + " DEBUG: " + x)
#define DEBUG_OUT_PRINTLN(x) DEBUG_PRINT(x + "\n")

#define BOOT0_SWITCH    PC_13
#define USB_HOST_ENABLE PA_15

// BEGIN CUSTOM CONFIGURATION DEFINITIONS

#define SM_DEBUG 0

// END CUSTOM CONFIGURATION DEFINITIONS

#endif // __CONFIGURATION_HPP__