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
#include <string.h>

#include "List.tpp"
#include "TMC5160.h"

#include "CORALS_Hardware.hpp"

#define CORALS_GIMBAL_MAX_POSITION CORALS_GIMBAL_STEPS_PER_REVOLUTION * CORALS_GIMBAL_MICROSTEPS * CORALS_GIMBAL_GEAR_RATIO

namespace CORALS {

namespace Hardware {

GimbalMotor::GimbalMotor(uint8_t chipSelect) : TMC5160_SPI(chipSelect, DEFAULT_F_CLK, SPISettings(4000000, MSBFIRST, SPI_MODE3), CORALS_SPI) {
    CORALS_SPI.begin();
    init();
}

GimbalMotor::~GimbalMotor() {
    end();
}

void GimbalMotor::init() {
    // Initialize the TMC5160
    TMC5160::PowerStageParameters powerParams;
    TMC5160::MotorParameters motorParams;

    begin(powerParams, motorParams, TMC5160::NORMAL_MOTOR_DIRECTION);
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
    enable_stallguard();

    // Gaslight
    setCurrentPosition(CORALS_GIMBAL_MAX_POSITION, true);
    setTargetPosition(0);

    // Gatekeep
    Set_OmegaG(5, 50);
    unsigned long start = millis(); 
    while (getDriverStatus() == TMC5160::OK && millis() - start < 10000) continue;

    // Girlboss
    setRampMode(TMC5160::HOLD_MODE);
    setCurrentPosition(M_PI/15, true);
    setTargetPosition(M_PI/15);
    Set_OmegaG(0);
    
    disable_stallguard();
}

float GimbalMotor::Get_ThetaG() {
    return steps_to_radians(getCurrentPosition());
}

float GimbalMotor::Get_OmegaG() {
    return sps_to_rpm(getCurrentSpeed());
}

void GimbalMotor::Set_OmegaG(float omegaG, float acceleration) {
    setAcceleration(rpm_to_sps(acceleration));
    setMaxSpeed(rpm_to_sps(omegaG));
}

bool GimbalMotor::Set_ICs(float thetaG, float maxSpeed, float acceleration) {
    setRampMode(TMC5160::POSITIONING_MODE);
    setMaxSpeed(rpm_to_sps(maxSpeed));
    setAcceleration(rpm_to_sps(acceleration));
    // setRampSpeeds(0.0, 0.0, 0.0);

    setTargetPosition(radians_to_steps(thetaG));

    while (!isTargetPositionReached()) {
        if (getDriverStatus() != TMC5160::OK) {
            return false;
        }
    }

    return true;
}

inline float GimbalMotor::radians_to_steps(const float radians) {
    return radians * CORALS_GIMBAL_STEPS_PER_REVOLUTION / 2/M_PI \
                   * CORALS_GIMBAL_GEAR_RATIO;
}

inline float GimbalMotor::steps_to_radians(const float steps) {
    return steps / CORALS_GIMBAL_STEPS_PER_REVOLUTION * 2*M_PI \
                 / CORALS_GIMBAL_GEAR_RATIO;
}

inline float GimbalMotor::rpm_to_sps(const float rpm) {
    return rpm * CORALS_GIMBAL_STEPS_PER_REVOLUTION / 60 \
               / CORALS_GIMBAL_GEAR_RATIO;
}

inline float GimbalMotor::sps_to_rpm(const float sps) {
    return sps * CORALS_GIMBAL_GEAR_RATIO * 60 \
               / CORALS_GIMBAL_STEPS_PER_REVOLUTION;
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

    m_omegaS_max = 10000;

    pinMode(m_pwmPin, OUTPUT);
    pinMode(m_dirPin, OUTPUT);
    pinMode(m_intPin, INPUT);
}

SpinMotor::~SpinMotor() {
    analogWrite(m_pwmPin, 0);
    disableInterrupt();
}

void SpinMotor::Set_Speed(const long omegaS) {
    const long speed = abs(omegaS);

    digitalWrite(m_dirPin, omegaS >= 0 ? HIGH : LOW);

    SERIAL_OUT_PRINT("Setting Speed to ");
    SERIAL_OUT.println(speed);
    analogWrite(m_pwmPin, map(speed, 0, m_omegaS_max, 0, 255));
}

SpinMotor::SpinSpeed SpinMotor::Get_Speed() {
    SpinSpeed retval = {
        .speed = 0.0,
        .success = m_encoder_state
    };

    // SERIAL_OUT_PRINT("Most Recent Data: ");
    // SERIAL_OUT.println(m_PWM_Data.RPM_History[m_PWM_Data.RPM_Index]);

    for (uint8_t i = 0; i < CORALS_SPIN_ENCODER_AVERAGE_LENGTH; i++) {
        retval.speed += m_PWM_Data.RPM_History[i] / CORALS_SPIN_ENCODER_AVERAGE_LENGTH;
    }

    return retval;
}

long SpinMotor::Get_MaxSpeed() {
    return m_omegaS_max;
}

void SpinMotor::Set_MaxSpeed(const long max) {
    SERIAL_OUT_PRINT("Setting Max Speed to ");
    SERIAL_OUT.println(max);
    m_omegaS_max = max;
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

IMU::IMU() : USBHostSerialDevice(true) {
  pinMode(USB_HOST_ENABLE, OUTPUT);
  digitalWrite(USB_HOST_ENABLE, HIGH);

  connect();
}

void IMU::connect() {
    while (!USBHostSerialDevice::connect()) {
        SERIAL_OUT_PRINTLN("No USB host Serial device connected");
        delay(5000);
    }

    begin(115200);
}

void IMU::run() {
    m_Data.index = 0;

    for (uint8_t i = 0; i < CORALS_IMU_AVERAGE_LENGTH; i++) {
        collect_data();
        parse_data();
    }
}

double IMU::Get_Roll() {
    return Get_Data(m_Data.roll);
}

double IMU::Get_Pitch() {
    return Get_Data(m_Data.pitch);
}

double IMU::Get_Yaw() {
    return Get_Data(m_Data.yaw);
}

double IMU::Get_Roll_Rate() {
    return Get_Data(m_Data.roll_rate);
}

double IMU::Get_Pitch_Rate() {
    return Get_Data(m_Data.pitch_rate);
}

double IMU::Get_Yaw_Rate() {
    return Get_Data(m_Data.yaw_rate);
}

void IMU::collect_data() {
    if (available()) {
        size_t bytes = 0;
        do {
            find("\n");
            bytes = readBytesUntil('\n', m_buffer, sizeof(m_buffer));
            strtok(m_buffer, "$VNYBA");
        } while (strtok(NULL, "$VNYBA") != NULL);
        
        m_buffer[bytes] = '\0';

        SERIAL_OUT_PRINT("Data: ");
        SERIAL_OUT.println(m_buffer);
    }
    else {
        SERIAL_OUT_PRINTLN("No data available.");
    }
}

void IMU::parse_data() {
    // Search for Preamble
    if (strtok(m_buffer, ",") == NULL) {
        m_Data.index++;
        return;
    }

    char *ptr;
    // Parse Yaw
    SERIAL_OUT_PRINT("Parsed Data: ");
    if ((ptr = strtok(NULL, ",")) != NULL) {
        m_Data.yaw[m_Data.index] = atof(ptr) * DEG_TO_RAD;
        SERIAL_OUT.print(m_Data.yaw[m_Data.index]);
        SERIAL_OUT.print(",");
    }

    // Parse Pitch
    if ((ptr = strtok(NULL, ",")) != NULL) {
        m_Data.pitch[m_Data.index] = atof(ptr) * DEG_TO_RAD;
        SERIAL_OUT.print(m_Data.pitch[m_Data.index]);
        SERIAL_OUT.print(",");
    }

    // Parse Roll
    if ((ptr = strtok(NULL, ",")) != NULL) {
        m_Data.roll[m_Data.index] = atof(ptr) * DEG_TO_RAD;
        SERIAL_OUT.print(m_Data.roll[m_Data.index]);
        SERIAL_OUT.print(",");
    }

    // Parse Yaw Rate
    if ((ptr = strtok(NULL, ",")) != NULL) {
        m_Data.yaw_rate[m_Data.index] = atof(ptr) / 60;
        SERIAL_OUT.print(m_Data.yaw_rate[m_Data.index]);
        SERIAL_OUT.print(",");
    }

    // Parse Pitch Rate
    if ((ptr = strtok(NULL, ",")) != NULL) {
        m_Data.pitch_rate[m_Data.index] = atof(ptr) / 60;
        SERIAL_OUT.print(m_Data.pitch_rate[m_Data.index]);
        SERIAL_OUT.print(",");
    }

    // Parse Roll Rate
    if ((ptr = strtok(NULL, ",")) != NULL) {
        m_Data.roll_rate[m_Data.index] = atof(ptr) / 60;
        SERIAL_OUT.println(m_Data.roll_rate[m_Data.index]);
    }

    m_Data.index++;
    m_buffer[0] = '\0';
}

double IMU::Get_Data(double *data) {
    double retval = 0.0;

    for (uint8_t i = 0; i < CORALS_IMU_AVERAGE_LENGTH; i++) {
        retval += data[i] / CORALS_IMU_AVERAGE_LENGTH;
    }

    return retval;
}

} // namespace Hardware

} // namespace CORALS