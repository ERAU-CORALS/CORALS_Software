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

        float Get_OmegaG();
        void Set_OmegaG(float omegaG, float acceleration = 10000);
        bool Set_ICs(float thetaG, float maxSpeed = 500, float acceleration = 1000);

    private:
        inline float degrees_to_steps(const float degrees);
        inline float steps_to_degrees(const float steps);
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
        void Set_Speed(const long velocity);

        long Get_MaxSpeed();
        void Set_MaxSpeed(const long max_speed);

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
        long m_max_speed;

        PWM_Data_t m_PWM_Data;
};

} // namespace Hardware

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