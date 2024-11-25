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

#include "List.tpp"
#include <Arduino.h>
#include "TMC5160_registers.h"
#include "TMC5160.h"

#ifdef GIGA_R1_M7

void initSpinners();
float angleToSteps(float angle);
int32_t velocityToSteps(float omegaG);
bool setICs(float targetAngle, float maxSpeed = 80, float acceleration = 200);
void cmdGimbalRate(TMC5160 &driver, float velocity);
void initSteppers(DataStructures::Vector::Vector<TMC5160*> &drivers, const TMC5160::PowerStageParameters &powerParams, const TMC5160::MotorParameters &motorParams, TMC5160::MotorDirection direction = TMC5160::NORMAL_MOTOR_DIRECTION);
void initSG2(DataStructures::Vector::Vector<TMC5160*> &drivers, uint8_t sgtValue = 5);
void findHome(DataStructures::Vector::Vector<TMC5160*> &drivers);

#endif