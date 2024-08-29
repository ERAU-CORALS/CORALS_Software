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

#include "Configuration.hpp"

#define CORALS_OUT SERIAL_OUT
const String CORALS_NAME = CORE_NAME + " CORALS";

#define CORALS_OUT_PRINT(x) CORALS_OUT.print(CORALS_NAME + ": " + x)
#define CORALS_OUT_PRINTLN(x) CORALS_OUT_PRINT(x + "\n")

#define CORALS_DEBUG_PRINT(x) if(DEBUG) CORALS_OUT.print(CORALS_NAME + " DEBUG: " + x)
#define CORALS_DEBUG_PRINTLN(x) CORALS_DEBUG_PRINT(x + "\n")

#endif // __CORALS_CONFIGURATION_HPP__