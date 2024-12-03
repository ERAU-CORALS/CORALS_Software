/**
 ********************************************************************************
 * @file    main.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS Main
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include <Arduino.h>
#include <SPI.h>
#include <SerialRPC.h>

#include "Configuration.hpp"
#include "CORALS_Configuration.hpp"
#include "CORALS_Hardware.hpp"

// #include "CORALS.hpp"
// #include "CORALS_Controller.hpp"

CORALS::Hardware::GimbalMotor *gimbalMotor1, *gimbalMotor2;
CORALS::Hardware::SpinMotor *spinMotor1, *spinMotor2;
// CORALS::Hardware::IMU *imu;

void setup_error(String message = "");

void setup() {
    // Serial Initialization
    Serial.begin(115200);
    const unsigned long serial_timer = millis();
    while (!Serial && (millis() - serial_timer < 10000)) continue;
    if (!Serial && DEBUG) {
        setup_error();
    }

    SERIAL_OUT_PRINTLN("Serial initialized for " + CORE_NAME + ".");

    // SPI Initialization
    SPI1.begin();

    SERIAL_OUT_PRINTLN("SPI1 initialized for " + CORE_NAME + ".");

    // RPC Initialization
    // if (!SerialRPC.begin()) {
    //     SERIAL_OUT_PRINTLN("Failed to initialize RPC on " + CORE_NAME + ".");
    // }

    // SERIAL_OUT_PRINTLN("RPC initialized on " + CORE_NAME + ".");

    // BEGIN CORALS CODE

    // CORALS::initialize();
    
    // END CORALS CODE

    // BEGIN CORALS DEBUG CODE

    // CORALS::Controller.init();

    SERIAL_OUT_PRINTLN("Creating Spin Motor Instances...");
    spinMotor1 = new CORALS::Hardware::SpinMotor(CORALS_CMG_1_PWM, CORALS_CMG_1_DIR, CORALS_CMG_1_INT);
    spinMotor2 = new CORALS::Hardware::SpinMotor(CORALS_CMG_2_PWM, CORALS_CMG_2_DIR, CORALS_CMG_2_INT);
    SERIAL_OUT_PRINTLN("Spin Motor Instance Created.");

    SERIAL_OUT_PRINTLN("Creating Gimbal Motor Instances...");
    gimbalMotor1 = new CORALS::Hardware::GimbalMotor(CORALS_CMG_1_CS);
    // gimbalMotor2 = new CORALS::Hardware::GimbalMotor(CORALS_CMG_2_CS);
    SERIAL_OUT_PRINTLN("Gimbal Motor Instance Created.");

    SERIAL_OUT_PRINTLN("Finding Gimbal Home...");
    gimbalMotor1->find_home();
    // gimbalMotor2->find_home();

    SERIAL_OUT_PRINTLN("Configuring Gimbal Coolstep...");
    gimbalMotor1->configure_coolstep();
    // gimbalMotor2->configure_coolstep();

    SERIAL_OUT_PRINTLN("Setting Gimbal ICs...");
    gimbalMotor1->Set_ICs(M_PI);
    // gimbalMotor2->Set_ICs(M_PI);

    SERIAL_OUT_PRINTLN("Setting Spin Speed 100%.");
    spinMotor1->Set_Speed(10000);
    spinMotor1->enableInterrupt();
    spinMotor2->Set_Speed(10000);
    spinMotor2->enableInterrupt();
    
    for (int i = 0; i < 10; ++i) {
        SERIAL_OUT_PRINT("Delaying for ");
        SERIAL_OUT.print((50 - 5 * i));
        SERIAL_OUT.println(" more seconds...");
        delay(5000);
    }

    SERIAL_OUT_PRINTLN("Setting Max Spin Speed.");
    spinMotor1->Set_MaxSpeed(spinMotor1->Get_Speed().speed);
    spinMotor2->Set_MaxSpeed(spinMotor2->Get_Speed().speed);
    SERIAL_OUT_PRINTLN("Setting Spin Speed 8800.");
    spinMotor1->Set_Speed(8800);
    spinMotor2->Set_Speed(8800);

    spinMotor1->disableInterrupt();
    spinMotor2->disableInterrupt();

    // imu = new CORALS::Hardware::IMU();

    // END CORALS DEBUG CODE
}

void loop() {
    // BEGIN CORALS CODE
    
    // CORALS::run();
    // CORALS::Controller_Run();

    // END CORALS CODE

    // BEGIN CORALS DEBUG CODE

    // SERIAL_OUT_PRINT(spinMotor->Get_Speed().speed);
    // SERIAL_OUT.print(" / ");
    // SERIAL_OUT.println(spinMotor->Get_MaxSpeed());

    // if (!imu->connected()) imu->connect();
    // else {
    //     imu->run();

    //     SERIAL_OUT_PRINT("Yaw: ");
    //     SERIAL_OUT.println(imu->Get_Yaw());
    //     SERIAL_OUT_PRINT("Pitch: ");
    //     SERIAL_OUT.println(imu->Get_Pitch());
    //     SERIAL_OUT_PRINT("Roll: ");
    //     SERIAL_OUT.println(imu->Get_Roll());

    //     SERIAL_OUT.println("");

    //     SERIAL_OUT_PRINT("Yaw Rate: ");
    //     SERIAL_OUT.println(imu->Get_Yaw_Rate());
    //     SERIAL_OUT_PRINT("Pitch Rate: ");
    //     SERIAL_OUT.println(imu->Get_Pitch_Rate());
    //     SERIAL_OUT_PRINT("Roll Rate: ");
    //     SERIAL_OUT.println(imu->Get_Roll_Rate());
    // }

    delay(1000);

    // END CORALS DEBUG CODE
}

void setup_error(String message) {
    if (message.length() > 0) SERIAL_OUT_PRINTLN(message);

#ifdef GIGA_R1_M7
    if (digitalRead(BOOT0_SWITCH) == LOW) {
        while (true) {
            digitalWrite(LEDR, LOW);
            delay(500);
            digitalWrite(LEDR, HIGH);
            delay(500);
        }
    }
#elif defined(GIGA_R1_M4)
    if (digitalRead(BOOT0_SWITCH) == HIGH) {
        while (true) {
            digitalWrite(LEDR, LOW);
            delay(500);
            digitalWrite(LEDR, HIGH);
            delay(500);
        }
    }
#endif // CPU_TYPE
}