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

#define CORALS_GIMBAL_MAX_POSITION CORALS_GIMBAL_STEPS_PER_REVOLUTION * CORALS_GIMBAL_MICROSTEPS * CORALS_GIMBAL_GEAR_RATIO

namespace CORALS {

namespace Hardware {

GimbalMotor::GimbalMotor(uint8_t chipSelect) : TMC5160_SPI(chipSelect, DEFAULT_F_CLK, SPISettings(4000000, MSBFIRST, SPI_MODE3), SPI1) {
    SPI1.begin();
    init();
}

GimbalMotor::~GimbalMotor() {
    end();
}

void GimbalMotor::init() {
    // Initialize the TMC5160
    TMC5160::PowerStageParameters powerParams;
    TMC5160::MotorParameters motorParams;

    SERIAL_OUT_PRINTLN("Calling GimbalMotor.begin()...");
    begin(powerParams, motorParams, TMC5160::NORMAL_MOTOR_DIRECTION);
    SERIAL_OUT_PRINTLN("GimbalMotor.begin() completed.");
}

void GimbalMotor::configure_coolstep() {
    writeRegister(TMC5160_Reg::TCOOLTHRS, 80000);
}

void GimbalMotor::enable_stallguard(int8_t threshold) {
    TMC5160_Reg::COOLCONF_Register coolConf;
    coolConf.value = readRegister(TMC5160_Reg::COOLCONF);
    coolConf.sgt = threshold;
    writeRegister(TMC5160_Reg::COOLCONF, coolConf.value);

    TMC5160_Reg::SW_MODE_Register swMode;
    swMode.value = readRegister(TMC5160_Reg::SW_MODE);
    swMode.sg_stop = 1;
    writeRegister(TMC5160_Reg::SW_MODE, swMode.value);
}


void GimbalMotor::disable_stallguard() {
    TMC5160_Reg::SW_MODE_Register swMode;
    swMode.value = readRegister(TMC5160_Reg::SW_MODE);
    swMode.sg_stop = 0;
    writeRegister(TMC5160_Reg::SW_MODE, swMode.value);

    init();
}

void GimbalMotor::find_home() {
    SERIAL_OUT_PRINTLN("Entering GimbalMotor::find_home()...");

    SERIAL_OUT_PRINTLN("Enabling Stallguard.");
    enable_stallguard();

    // Gaslight
    SERIAL_OUT_PRINTLN("Find Home: Gaslighting...");
    SERIAL_OUT_PRINTLN("Setting current position to 360.");
    setCurrentPosition(CORALS_GIMBAL_MAX_POSITION, true);
    SERIAL_OUT_PRINTLN("Setting target position to 0.");
    setTargetPosition(0);

    // Gatekeep
    SERIAL_OUT_PRINTLN("Find Home: Gatekeeping...");
    SERIAL_OUT_PRINTLN("Setting OmegaG to -50.");
    Set_OmegaG(50, 25);
    unsigned long start = millis(); 
    while (getDriverStatus() == TMC5160::OK && millis() - start < 10000) continue;

    // Girlboss
    SERIAL_OUT_PRINTLN("Find Home: Girlbossing...");
    SERIAL_OUT_PRINTLN("Commanding HOLD POSITION.");
    setRampMode(TMC5160::HOLD_MODE);
    SERIAL_OUT_PRINTLN("Setting current position to 0.");
    setCurrentPosition(0, true);
    SERIAL_OUT_PRINTLN("Setting target position to 0.");
    setTargetPosition(0);
    SERIAL_OUT_PRINTLN("Commanding Stopping Rotation.");
    Set_OmegaG(0);
    
    SERIAL_OUT_PRINTLN("Disabling Stallguard.");
    disable_stallguard();

    SERIAL_OUT_PRINTLN("Exiting GimbalMotor::find_home().");
}

float GimbalMotor::Get_OmegaG() {
    return steps_to_degrees(getCurrentSpeed()) * DEG_TO_RAD;
}

void GimbalMotor::Set_OmegaG(float omegaG, float acceleration) {
    setAcceleration(acceleration);
    setMaxSpeed(degrees_to_steps(omegaG));
}

bool GimbalMotor::Set_ICs(float thetaG, float maxSpeed, float acceleration) {
    setRampMode(TMC5160::POSITIONING_MODE);
    setMaxSpeed(maxSpeed);
    setAcceleration(acceleration);
    // setRampSpeeds(0.0, 0.0, 0.0);

    setTargetPosition(degrees_to_steps(thetaG));

    while (!isTargetPositionReached()) {
        if (getDriverStatus() != TMC5160::OK) {
            return false;
        }
    }

    return true;
}

inline float GimbalMotor::degrees_to_steps(const float degrees) {
    return degrees * CORALS_GIMBAL_STEPS_PER_REVOLUTION / 360.0 \
                   * CORALS_GIMBAL_GEAR_RATIO;
                //    * CORALS_GIMBAL_MICROSTEPS 
}

inline float GimbalMotor::steps_to_degrees(const float steps) {
    return steps / CORALS_GIMBAL_STEPS_PER_REVOLUTION * 360.0 \
                 / CORALS_GIMBAL_GEAR_RATIO;
}

void Encoder_ISR(SpinMotor::PWM_Data_t *const data) {
    unsigned long current_call_us = micros();

    double new_data = 1.0e6 / (current_call_us - data->last_call_us); // Steps per second
    new_data /= CORALS_SPIN_ENCODER_STEPS; // Encoder-Revolutions per second
    new_data /= CORALS_SPIN_ENCODER_GEAR_RATIO; // Motor-Revolutions per second
    new_data *= 60; // Motor-Revolutions per minute 

    data->RPM_History[data->RPM_Index] = new_data;

    data->last_call_us = current_call_us;
    ++data->RPM_Index %= CORALS_SPIN_ENCODER_AVERAGE_LENGTH;
}

SpinMotor::SpinMotor(uint8_t pwmPin, uint8_t dirPin, uint8_t intPin) {
    m_pwmPin = pwmPin;
    m_dirPin = dirPin;
    m_intPin = intPin;

    m_max_speed = 10000;

    pinMode(m_pwmPin, OUTPUT);
    pinMode(m_dirPin, OUTPUT);
    pinMode(m_intPin, INPUT);
}

SpinMotor::~SpinMotor() {
    analogWrite(m_pwmPin, 0);
    disableInterrupt();
}

void SpinMotor::Set_Speed(const long velocity) {
    const long speed = abs(velocity);

    digitalWrite(m_dirPin, velocity >= 0 ? HIGH : LOW);

    SERIAL_OUT_PRINT("Setting Speed to ");
    SERIAL_OUT.println(speed);
    analogWrite(m_pwmPin, map(speed, 0, m_max_speed, 0, 255));
}

SpinMotor::SpinSpeed SpinMotor::Get_Speed() {
    SpinSpeed retval = {
        .speed = 0.0,
        .success = false
    };
    
    if (!m_encoder_state) return retval;

    // SERIAL_OUT_PRINT("Most Recent Data: ");
    // SERIAL_OUT.println(m_PWM_Data.RPM_History[m_PWM_Data.RPM_Index]);

    for (uint8_t i = 0; i < CORALS_SPIN_ENCODER_AVERAGE_LENGTH; i++) {
        retval.speed += m_PWM_Data.RPM_History[i] / CORALS_SPIN_ENCODER_AVERAGE_LENGTH;
    }

    retval.success = true;

    return retval;
}

long SpinMotor::Get_MaxSpeed() {
    return m_max_speed;
}

void SpinMotor::Set_MaxSpeed(const long max_speed) {
    SERIAL_OUT_PRINT("Setting Max Speed to ");
    SERIAL_OUT.println(max_speed);
    m_max_speed = max_speed;
}

void SpinMotor::enableInterrupt() {
    attachInterrupt(digitalPinToInterrupt(m_intPin), Encoder_ISR, RISING, &m_PWM_Data);
    m_encoder_state = true;
}

void SpinMotor::disableInterrupt() {
    detachInterrupt(digitalPinToInterrupt(m_intPin));
    m_encoder_state = false;

    for (double &rpm : m_PWM_Data.RPM_History) rpm = 0.0;\
    m_PWM_Data.RPM_Index = 0;
    m_PWM_Data.last_call_us = 0;
}

} // namespace Hardware

}