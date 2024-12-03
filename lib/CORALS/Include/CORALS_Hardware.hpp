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

#include <Arduino.h>
#include <TMC5160_registers.h>
#include <TMC5160.h>
#include <USBHostSerialDevice.h>

#include "Vector.tpp"

namespace CORALS {

namespace Hardware {

class GimbalMotor : public TMC5160_SPI {
    public:
        GimbalMotor(uint8_t chipSelect);
        ~GimbalMotor();
        
        void init();
        
        void configure_coolstep();
        void enable_stallguard(int8_t threshold = -5);
        void disable_stallguard();

        void find_home();

        float Get_ThetaG();
        float Get_OmegaG();
        void Set_OmegaG(float omegaG, float acceleration = 500);
        bool Set_ICs(float thetaG, float maxSpeed = 30, float acceleration = 500);

    private:
        inline float radians_to_steps(const float radians);
        inline float steps_to_radians(const float steps);
        inline float rpm_to_sps(const float rpm);
        inline float sps_to_rpm(const float sps);
};

class SpinMotor {
    public:
        SpinMotor(uint8_t pwmPin, uint8_t dirPin, uint8_t intPin);
        ~SpinMotor();

        struct SpinSpeed {
            double speed;
            bool success;
        };

        SpinSpeed Get_Speed();
        void Set_Speed(const long omegaS);

        long Get_MaxSpeed();
        void Set_MaxSpeed(const long max);

        void enableInterrupt();
        void disableInterrupt();

        struct PWM_Data_t {
            double RPM_History[CORALS_SPIN_ENCODER_AVERAGE_LENGTH];
            uint8_t RPM_Index;
            unsigned long last_call_us;
        };

    private:
        uint8_t m_pwmPin;
        uint8_t m_dirPin;
        uint8_t m_intPin;

        bool m_encoder_state;
        long m_omegaS_max;

        PWM_Data_t m_PWM_Data;
};

class IMU : public USBHostSerialDevice {
    public:
        IMU();
        ~IMU() {};

        void connect();

        void run();

        double Get_Roll();
        double Get_Pitch();
        double Get_Yaw();

        double Get_Roll_Rate();
        double Get_Pitch_Rate();
        double Get_Yaw_Rate();

    private:
        struct IMU_Data {
            double yaw[CORALS_IMU_AVERAGE_LENGTH];
            double pitch[CORALS_IMU_AVERAGE_LENGTH];
            double roll[CORALS_IMU_AVERAGE_LENGTH];

            double yaw_rate[CORALS_IMU_AVERAGE_LENGTH];
            double pitch_rate[CORALS_IMU_AVERAGE_LENGTH];
            double roll_rate[CORALS_IMU_AVERAGE_LENGTH];

            uint8_t index;
        } m_Data;

        char m_buffer[128];

        void collect_data();
        void parse_data();

        double Get_Data(double *data);
};

} // namespace Hardware

} // namespace CORALS

#endif // __CORALS_HARDWARE_HPP__