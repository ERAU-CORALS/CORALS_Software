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
#include <SerialRPC.h>

#include "Configuration.hpp"

#include "CORALS.hpp"
#include "CORALS_Configuration.hpp"
#include "CORALS_Hardware.hpp"

CORALS::Hardware::GimbalMotor *gimbalMotor;
CORALS::Hardware::SpinMotor *spinMotor;

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

    SERIAL_OUT_PRINTLN("Creating Spin Motor Instance...");
    spinMotor = new CORALS::Hardware::SpinMotor(CORALS_CMG_1_PWM, CORALS_CMG_1_DIR, CORALS_CMG_1_INT);
    SERIAL_OUT_PRINTLN("Spin Motor Instance Created.");

    SERIAL_OUT_PRINTLN("Creating Gimbal Motor Instance...");
    gimbalMotor = new CORALS::Hardware::GimbalMotor(CORALS_CMG_1_CS);
    SERIAL_OUT_PRINTLN("Gimbal Motor Instance Created.");

    SERIAL_OUT_PRINTLN("Finding Gimbal Home...");
    gimbalMotor->find_home();

    SERIAL_OUT_PRINTLN("Configuring Gimbal Coolstep...");
    gimbalMotor->configure_coolstep();

    SERIAL_OUT_PRINTLN("Setting Gimbal ICs...");
    gimbalMotor->Set_ICs(180);

    SERIAL_OUT_PRINTLN("Setting Spin Speed 100%.");
    spinMotor->Set_Speed(10000);
    spinMotor->enableInterrupt();
    
    for (int i = 0; i < 10; ++i) {
        SERIAL_OUT_PRINT("Current Speed: ");
        SERIAL_OUT.println(spinMotor->Get_Speed().speed);
        SERIAL_OUT_PRINT("Delaying for ");
        SERIAL_OUT.print((50 - 5 * i));
        SERIAL_OUT.println(" more seconds...");
        delay(5000);
    }

    SERIAL_OUT_PRINTLN("Setting Max Spin Speed.");
    spinMotor->Set_MaxSpeed(spinMotor->Get_Speed().speed);
    SERIAL_OUT_PRINTLN("Setting Spin Speed 8500.");
    spinMotor->Set_Speed(8500);

    spinMotor->disableInterrupt();
    spinMotor->enableInterrupt();

    // END CORALS DEBUG CODE
}

void loop() {
    // BEGIN CORALS CODE
    
    // CORALS::run();

    // END CORALS CODE

    // BEGIN CORALS DEBUG CODE

    SERIAL_OUT_PRINT(spinMotor->Get_Speed().speed);
    SERIAL_OUT.print(" / ");
    SERIAL_OUT.println(spinMotor->Get_MaxSpeed());

    delay(1000);

    // END CORALS DEBUG CODE
}

void setup_error(String message) {
    if (message.length() > 0) SERIAL_OUT_PRINTLN(message);

#ifdef GIGA_R1_M7
    if (digitalRead(PC_13) == LOW) {
        while (true) {
            digitalWrite(LEDR, LOW);
            delay(500);
            digitalWrite(LEDR, HIGH);
            delay(500);
        }
    }
#elif defined(GIGA_R1_M4)
    if (digitalRead(PC_13) == HIGH) {
        while (true) {
            digitalWrite(LEDR, LOW);
            delay(500);
            digitalWrite(LEDR, HIGH);
            delay(500);
        }
    }
#endif // CPU_TYPE
}