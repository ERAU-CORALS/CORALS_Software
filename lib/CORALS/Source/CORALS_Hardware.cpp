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

#include "CORALS_Hardware.hpp"
#include "List.tpp"
#include <Arduino.h>
#include "TMC5160_registers.h"
#include "TMC5160.h"

namespace CORALS {

#ifdef GIGA_R1_M7

const int SPINNER_DIR = 28; // Spinner Direction Pins
DataStructures::List::List<int> spinnerPinList; // Spinner Speed Pins

// NOTE: DEFINE SPINNER SPEEDS AS CONSTANTS
void initSpinners() {
    for (int i = 0; i < spinnerPinList.length(); i++) { // Prime the spinner motors
        pinMode(spinnerPinList[i], OUTPUT); // Init spinner pins to output
        analogWrite(spinnerPinList[i],Speed); // Write speed to spinners
    }
    digitalWrite(SPINNER_DIR,HIGH); // Write direction to spinners (should all be same pin for direction)
}

float angleToSteps(float angle) {
        // Convert angle in degrees to motor steps
        return (angle * STEPS_PER_REV * MICROSTEPS * GEAR_RATIO) / 360.0;
    }

float velocityToSteps(float omegaG) {
    float stepsPerSecond = (omegaG*200)/(2*M_PI*256);
    return (stepsPerSecond*(1ul<<24))/12000000;
}

bool setICs(float targetAngle, float maxSpeed = 80, float acceleration = 200)
{
    // Convert angle to steps
    float steps = angleToSteps(targetAngle);

    // Configure motion profile
    driver->setMaxSpeed(maxSpeed);         // steps/second
    driver->setAcceleration(acceleration); // steps/second^2
    driver->setRampSpeeds(0.0, 0.0, 0.0);  // Start speed, stop speed, transition speed

    // Set target position
    driver->setRampMode(TMC5160::POSITIONING_MODE);
    driver->setTargetPosition(steps);

    // Wait for position reached
    while (!driver->isTargetPositionReached())
    {
        // Check for errors
        TMC5160::DriverStatus status = driver->getDriverStatus();
        if (status != TMC5160::OK)
        {
            return false;
        }
    }

    return true;
}

void cmdGimbalRate(TMC5160 &driver, float velocity) {
    if (velocity >= 0) {
        driver.writeRegister(TMC5160_Reg::RAMPMODE, TMC5160_Reg::VELOCITY_MODE_POS);
    } else {
        driver.writeRegister(TMC5160_Reg::RAMPMODE, TMC5160_Reg::VELOCITY_MODE_NEG);
        velocity = -velocity; // Make velocity positive for the register
    }
    driver.writeRegister(TMC5160_Reg::VMAX, velocityToSteps(velocity));
}

void initSteppers(DataStructures::Vector::Vector<TMC5160*> &drivers, const TMC5160::PowerStageParameters &powerParams, const TMC5160::MotorParameters &motorParams, TMC5160::MotorDirection direction = TMC5160::NORMAL_MOTOR_DIRECTION) {
    for (unsigned int i = 0; i < drivers.length(); i++) {
        if (drivers.get(i) != nullptr) {
            drivers.get(i)->begin(powerParams, motorParams, direction);
        }
    }
}

void initSG2(DataStructures::Vector::Vector<TMC5160*> &drivers, uint8_t sgtValue = 5){
    for (unsigned int i = 0; i < drivers.length(); i++) {
        if (drivers.get(i) != nullptr) {
            TMC5160_Reg::COOLCONF_Register coolConf; // SGThreshold, 
            coolConf.value = drivers.get(i)->readRegister(TMC5160_Reg::COOLCONF);
            coolConf.sgt = sgtValue;
            drivers.get(i)->writeRegister(TMC5160_Reg::COOLCONF, coolConf.value);

            TMC5160_Reg::SW_MODE_Register swMode; // SG_STOP
            swMode.value = drivers.get(i)->readRegister(TMC5160_Reg::SW_MODE);
            swMode.sg_stop = 1;
            drivers.get(i)->writeRegister(TMC5160_Reg::SW_MODE, swMode.value);

            drivers.get(i)->writeRegister(TMC5160_Reg::TCOOLTHRS, 80000);
            drivers.get(i)->writeRegister(TMC5160_Reg::AMAX, 10000);
            drivers.get(i)->writeRegister(TMC5160_Reg::VMAX, 100000);
            drivers.get(i)->writeRegister(TMC5160_Reg::XACTUAL, 0);
            drivers.get(i)->writeRegister(TMC5160_Reg::XTARGET, 300);
        }
    }
}

void findHome(DataStructures::Vector::Vector<TMC5160*> &drivers) {
    TMC5160_Reg::RAMP_STAT_Register rampStat;
    TMC5160_Reg::SW_MODE_Register swMode; // SG_STOP
    if (rampStat.status_sg == 1) {
        drivers.get(i)->setRampMode(TMC5160::HOLD_MODE);
        drivers.get(i)->writeRegister(TMC5160_Reg::XACTUAL, 0);
        drivers.get(i)->writeRegister(TMC5160_Reg::XTARGET, 0);
        swMode.value = drivers.get(i)->readRegister(TMC5160_Reg::SW_MODE);
        swMode.sg_stop = 0;
        drivers.get(i)->writeRegister(TMC5160_Reg::SW_MODE, swMode.value);
    }
}

#endif

}