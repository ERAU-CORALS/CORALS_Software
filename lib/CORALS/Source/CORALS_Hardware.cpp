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

#include "CORALS_Configuration.hpp"

#include <Arduino.h>

#include "List.tpp"
#include "TMC5160.h"

#include "CORALS_Hardware.hpp"

namespace CORALS {

namespace Hardware {

GimbalMotor::GimbalMotor(uint8_t chipSelect) : TMC5160_SPI(chipSelect) {
    const TMC5160::PowerStageParameters powerParams = {
        .drvStrength = 2,
        .bbmTime = 0,
        .bbmClks = 4
    };

    const TMC5160::MotorParameters motorParams = {
        .globalScaler = 32,
        .irun = 16,
        .ihold = 0,
        .freewheeling = TMC5160_Reg::FREEWHEEL_NORMAL,
        .pwmOfsInitial = 30,
        .pwmGradInitial = 0
    };

    begin(powerParams, motorParams, TMC5160::NORMAL_MOTOR_DIRECTION);
}

GimbalMotor::~GimbalMotor() {
    end();
}

void GimbalMotor::enable_stallguard(uint8_t threshold) {
    TMC5160_Reg::COOLCONF_Register coolConf;
    coolConf.value = readRegister(TMC5160_Reg::COOLCONF);
    coolConf.sgt = threshold;
    writeRegister(TMC5160_Reg::COOLCONF, coolConf.value);

    TMC5160_Reg::SW_MODE_Register swMode;
    swMode.value = readRegister(TMC5160_Reg::SW_MODE);
    swMode.sg_stop = 1;
    writeRegister(TMC5160_Reg::SW_MODE, swMode.value);

    writeRegister(TMC5160_Reg::TCOOLTHRS, 80000);
    writeRegister(TMC5160_Reg::AMAX, 10000);
    writeRegister(TMC5160_Reg::VMAX, 100000);
    writeRegister(TMC5160_Reg::XACTUAL, 0);
    writeRegister(TMC5160_Reg::XTARGET, 300);
}

void GimbalMotor::find_home() {
    TMC5160_Reg::RAMP_STAT_Register rampStat;
    rampStat.value = readRegister(TMC5160_Reg::RAMP_STAT);

    if (rampStat.status_sg) {
        setRampMode(TMC5160::HOLD_MODE);
        writeRegister(TMC5160_Reg::XACTUAL, 0);
        writeRegister(TMC5160_Reg::XTARGET, 0);

        TMC5160_Reg::SW_MODE_Register swMode;
        swMode.value = readRegister(TMC5160_Reg::SW_MODE);
        swMode.sg_stop = 0;
        writeRegister(TMC5160_Reg::SW_MODE, swMode.value);
    }
}

void GimbalMotor::Set_OmegaG(float omegaG) {
    if (omegaG >= 0) {
        writeRegister(TMC5160_Reg::RAMPMODE, TMC5160_Reg::VELOCITY_MODE_POS);
    } else {
        writeRegister(TMC5160_Reg::RAMPMODE, TMC5160_Reg::VELOCITY_MODE_NEG);
        omegaG = -omegaG; // Make omegaG positive for the register
    }

    auto velocity_to_steps = [](float omegaG) { return (((omegaG*200) / (2*M_PI*256))*(1ul << 24)) / 12000000; };
    writeRegister(TMC5160_Reg::VMAX, velocity_to_steps(omegaG));
}

bool GimbalMotor::Set_ICs(float thetaG, float maxSpeed, float acceleration) {
    setMaxSpeed(maxSpeed);
    setAcceleration(acceleration);
    setRampSpeeds(0.0, 0.0, 0.0);

    setRampMode(TMC5160::POSITIONING_MODE);
    setTargetPosition(degrees_to_steps(thetaG));

    while (!isTargetPositionReached()) {
        if (getDriverStatus() != TMC5160::OK) {
            return false;
        }
    }

    return true;
}

float GimbalMotor::degrees_to_steps(const float degrees) {
    return degrees * CORALS_GIMBAL_STEPS_PER_REVOLUTION / 360.0 \
                   * CORALS_GIMBAL_MICROSTEPS \
                   * CORALS_GIMBAL_GEAR_RATIO;
}

SpinMotor::SpinMotor(uint8_t pwmPin, uint8_t dirPin, uint8_t intPin) {
    m_pwmPin = pwmPin;
    m_dirPin = dirPin;
    m_intPin = intPin;

    pinMode(m_pwmPin, OUTPUT);
    pinMode(m_dirPin, OUTPUT);
    pinMode(m_intPin, INPUT);
}

SpinMotor::~SpinMotor() {
    analogWrite(m_pwmPin, 0);
    disableInterrupt();
}

void SpinMotor::setSpeed(const float velocity) {
    const uint8_t speed = (uint8_t)abs(velocity);

    digitalWrite(m_dirPin, velocity >= 0 ? HIGH : LOW);
    analogWrite(m_pwmPin, speed);
}

void SpinMotor::enableInterrupt() {
    attachInterrupt(digitalPinToInterrupt(m_intPin), Encoder_ISR, RISING);
}

void SpinMotor::disableInterrupt() {
    detachInterrupt(digitalPinToInterrupt(m_intPin));
}

} // namespace Hardware

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

#endif

}