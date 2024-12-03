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

#if !defined(CORALS_DEBUG) || CORALS_DEBUG > 1
    #ifdef CORALS_DEBUG
        #undef CORALS_DEBUG
    #endif
    #define CORALS_DEBUG DEBUG
#endif

#define CORALS_OUT_PRINT(x) CORALS_OUT.print(CORALS_NAME + ": " + x)
#define CORALS_OUT_PRINTLN(x) CORALS_OUT_PRINT(x + "\n")

#define CORALS_DEBUG_PRINT(x) if(CORALS_DEBUG) CORALS_OUT.print(CORALS_NAME + " DEBUG: " + x)
#define CORALS_DEBUG_PRINTLN(x) CORALS_DEBUG_PRINT(x + "\n")

// BEGIN CORALS CONFIGURATION SETTINGS

#define CORALS_CMG_COUNT 2

// END CORALS CONFIGURATION SETTINGS

#define CORALS_FUTURE_RESERVED -1

// BEGIN CORALS ARDUINO CONFIGURATION

#define CORALS_DEBUG_BUTTON PC_13

#define CORALS_SPI_SCK      13
#define CORALS_SPI_CIPO     12
#define CORALS_SPI_COPI     11

#define CORALS_CMG_1_CS     22
#define CORALS_CMG_1_PWM    3
#define CORALS_CMG_1_DIR    2
#define CORALS_CMG_1_INT    48

#define CORALS_CMG_2_CS     24
#define CORALS_CMG_2_PWM    4
#define CORALS_CMG_2_DIR    2
#define CORALS_CMG_2_INT    49

#define CORALS_CMG_3_CS     26
#define CORALS_CMG_3_PWM    5
#define CORALS_CMG_3_DIR    2
#define CORALS_CMG_3_INT    50

#define CORALS_CMG_4_CS     28
#define CORALS_CMG_4_PWM    6
#define CORALS_CMG_4_DIR    2
#define CORALS_CMG_4_INT    51

#define CORALS_CMG_5_CS     30
#define CORALS_CMG_5_PWM    7
#define CORALS_CMG_5_DIR    2
#define CORALS_CMG_5_INT    52

#define CORALS_CMG_6_CS     32
#define CORALS_CMG_6_PWM    8
#define CORALS_CMG_6_DIR    2
#define CORALS_CMG_6_INT    53

#define CORALS_CMG_7_CS     CORALS_FUTURE_RESERVED
#define CORALS_CMG_7_PWM    CORALS_FUTURE_RESERVED
#define CORALS_CMG_7_DIR    CORALS_FUTURE_RESERVED
#define CORALS_CMG_7_INT    CORALS_FUTURE_RESERVED

#define CORALS_CMG_8_CS     CORALS_FUTURE_RESERVED
#define CORALS_CMG_8_PWM    CORALS_FUTURE_RESERVED
#define CORALS_CMG_8_DIR    CORALS_FUTURE_RESERVED
#define CORALS_CMG_8_INT    CORALS_FUTURE_RESERVED

// END CORALS ARDUINO CONFIGURATION

// BEGIN CORALS HARDWARE CONFIGURATION

#define CORALS_GIMBAL_STEPS_PER_REVOLUTION 200
#define CORALS_GIMBAL_MICROSTEPS 256
#define CORALS_GIMBAL_GEAR_RATIO 1
#define CORALS_GIMBAL_INERTIA 0.000055 // kg*m^2

#define CORALS_GIMBAL_MAX_SPEED 150.0f // degrees per second

#define CORALS_SPIN_ENCODER_STEPS 12
#define CORALS_SPIN_ENCODER_GEAR_RATIO 1
#define CORALS_SPIN_MOTOR_SPEED 72000 // degrees per second

#define CORALS_GIMBAL_ANGULAR_MOMENTUM CORALS_SPIN_MOTOR_SPEED * CORALS_GIMBAL_INERTIA * DEG_TO_RAD

#define CORALS_SPIN_ENCODER_AVERAGE_LENGTH 50

// END CORALS HARDWARE CONFIGURATION

#endif // __CORALS_CONFIGURATION_HPP__