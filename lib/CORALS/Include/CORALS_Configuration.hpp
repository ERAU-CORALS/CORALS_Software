/**
 ********************************************************************************
 * @file    CORALS_Configuration.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS Configuration for Arduino MEGA 2560
 * @version 1.0
 * @date    2024-03-20
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __CORALS_CONFIGURATION_HPP__
#define __CORALS_CONFIGURATION_HPP__

#include <Arduino.h>
#include <SerialRPC.h>

// Serial USART Allocation
#ifdef GIGA_R1_M4

#define DEBUG_OUT Serial
const String CORE_NAME = "GIGA_R1_M4";

#endif

#ifdef GIGA_R1_M7

#define DEBUG_OUT SerialRPC
const String CORE_NAME = "GIGA_R1_M7";

#endif

#define DEBUG_PRINT(x) DEBUG_OUT.print(CORE_NAME + ": " + x)
#define DEBUG_PRINTLN(x) DEBUG_OUT.println(CORE_NAME + ": " + x)

#endif // __CORALS_CONFIGURATION_HPP__