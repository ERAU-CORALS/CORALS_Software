/**
 ********************************************************************************
 * @file    CORALS_Hardware.cpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   Hardware Integration
 * @version 1.0
 * @date    2024-08-21
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __CORALS_HARDWARE_HPP__
#define __CORALS_HARDWARE_HPP__

#include "Vector.tpp"
#include <Arduino.h>
#include "TMC5160_registers.h"
#include "TMC5160.h"

#ifdef GIGA_R1_M7

namespace CORALS {

#define CS1 10
#define CS2 11
#define CS3 12
#define CS4 13
#define CS5 14
#define CS6 15
#define SPIN_PIN 28
#define Speed 255

#define STEPS_PER_REV 200
#define MICROSTEPS 256
#define GEAR_RATIO 1

TMC5160_SPI driver1(CS1);
TMC5160_SPI driver2(CS2);
TMC5160_SPI driver3(CS3);
TMC5160_SPI driver4(CS4);
TMC5160_SPI driver5(CS5);
TMC5160_SPI driver6(CS6);

void initSpinners();
float angleToSteps(float angle);
int32_t velocityToSteps(float omegaG);
bool setICs(float targetAngle, float maxSpeed = 80, float acceleration = 200);
void cmdGimbalRate(TMC5160 &driver, float velocity);
void initSteppers(::DataStructures::Vector::Vector<TMC5160*> &drivers, const TMC5160::PowerStageParameters &powerParams, const TMC5160::MotorParameters &motorParams, TMC5160::MotorDirection direction = TMC5160::NORMAL_MOTOR_DIRECTION);
void initSG2(::DataStructures::Vector::Vector<TMC5160*> &drivers, uint8_t sgtValue = 5);
void findHome(::DataStructures::Vector::Vector<TMC5160*> &drivers);

} // namespace CORALS

#endif // GIGA_R1_M7

#endif // __CORALS_HARDWARE_HPP__