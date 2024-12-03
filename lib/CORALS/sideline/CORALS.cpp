/**
 ********************************************************************************
 * @file    CORALS.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS Software Core
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "CORALS.hpp"

#include <Arduino.h>

#include "CORALS_Configuration.hpp"
#include "CORALS_API.hpp"
#include "CORALS_Blinky.hpp"
#include "CORALS_Controller.hpp"
#include "CORALS_DataStore.hpp"
#include "CORALS_Hardware.hpp"
#include "CORALS_Telecommunicator.hpp"
#include "StateManager.hpp"

namespace CORALS {

namespace {

::StateManager::StateManager CORALS_OS;
::CORALS::Hardware::IMU IMU;

#ifdef GIGA_R1_M7
void IMU_Run() {
    IMU.run();
    const double yaw = IMU.Get_Yaw();
    const double pitch = IMU.Get_Pitch();
    const double roll = IMU.Get_Roll();

    Set_Attitude_Q1(sin(roll/2)*cos(pitch/2)*cos(yaw/2) - cos(roll/2)*sin(pitch/2)*sin(yaw/2));
    Set_Attitude_Q2(sin(roll/2)*cos(pitch/2)*sin(yaw/2) + cos(roll/2)*sin(pitch/2)*cos(yaw/2));
    Set_Attitude_Q3(cos(roll/2)*cos(pitch/2)*sin(yaw/2) - sin(roll/2)*sin(pitch/2)*cos(yaw/2));
    Set_Attitude_Q0(cos(roll/2)*cos(pitch/2)*cos(yaw/2) + sin(roll/2)*sin(pitch/2)*sin(yaw/2));

    DVector rates(3);
    rates.set(0, IMU.Get_Yaw_Rate());
    rates.set(1, IMU.Get_Pitch_Rate());
    rates.set(2, IMU.Get_Roll_Rate());
}
#endif

} // end namespace

void initialize() {
    CORALS_OUT_PRINTLN("CORALS Initializing...");

    CORALS_OS.Register("Blinky", Blinky, 1000, ::StateManager::SM_Priority::PRIORITY_HIGHEST);
#ifdef GIGA_R1_M7
    DS_Init();
    // CORALS_OS.Register("Controller", Controller_Run, 100, ::StateManager::SM_Priority::PRIORITY_HIGH);
    // CORALS_OS.Register("IMU", IMU_Run, 200, ::StateManager::SM_Priority::PRIORITY_MEDIUM);
#elif defined(GIGA_R1_M4)
    TC_Init();
    CORALS_OS.Register("Telecommunicator", TC_Run, 100, ::StateManager::SM_Priority::PRIORITY_MEDIUM);
#endif


    CORALS_OUT_PRINTLN("CORALS Initialized.");
}

void run() {
    CORALS_DEBUG_PRINTLN("CORALS Loop.");

    CORALS_OS.Run();

    if (digitalRead(CORALS_DEBUG_BUTTON) == HIGH) {
        delay(1000);
    }

#ifdef GIGA_R1_M7
    while (SerialRPC.available()) Serial.write(SerialRPC.read());
    Serial.flush();
#endif
}

} // end namespace CORALS