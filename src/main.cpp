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

DataStructures::Vector::Vector<double> thetaG_k;  // Declare global
Quaternion qError;
Quaternion currentTarget;
double phiError;
double errorCount;
double gyroModifier;
DataStructures::Vector::Vector<double> commanded_wG;
Matrix::Matrix<double> DCM_BG;
Vector<double> targetT_LQR;
Vector<double> xVector;

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

    // RPC Initialization
    if (!SerialRPC.begin()) {
        SERIAL_OUT_PRINTLN("Failed to initialize RPC on " + CORE_NAME + ".");
    }

    SERIAL_OUT_PRINTLN("RPC initialized on " + CORE_NAME + ".");

    // BEGIN CORALS CODE

    TC_Init();

    DataStructures::Vector::Vector<TMC5160*> drivers(6);
    drivers.set(0, &driver1);
    drivers.set(1, &driver2);
    drivers.set(2, &driver3);
    drivers.set(3, &driver4);
    drivers.set(4, &driver5);
    drivers.set(5, &driver6);

    // Define power stage parameters
    TMC5160::PowerStageParameters powerParams;
    powerParams.drvStrength = 2;
    powerParams.bbmTime = 0;
    powerParams.bbmClks = 4;

    // Define motor parameters
    const int N = 4;  // Number of states/dimensions
    TMC5160::MotorParameters motorParams;
    motorParams.globalScaler = 32;
    motorParams.irun = 16;
    motorParams.ihold = 0;
    motorParams.freewheeling = TMC5160_Reg::FREEWHEEL_NORMAL;
    motorParams.pwmOfsInitial = 30;
    motorParams.pwmGradInitial = 0;

    CORALS::initialize();
    CORALS::initSpinners();
    CORALS::initializeSteppers(drivers, powerParams, motorParams);
    CORALS::initSG2(drivers, 5); 
    Matrix::Matrix<double> thetaGICs = CORALS::get_thetaGICs(4); // Initial Conditions
    DCM_BG = CORALS::getDCM_BG(4); // DCM Body to Gimbal

    thetaG_ICs = get_thetaGICs(N);
    errorCount = 0;
    gyroModifier = 1;
    commanded_wG = DataStructures::Vector::Vector<double>(3);

    CORALS::setICs(thetaG_ICs,80,200); // Command gimbals to ICs

    // Retrieve from API
    GainMatrix gain_LQR; // Get Gains
    TargetList *targetList = nullptr; // Init Targets
    DataStore.get(TARGET_LIST, &targetList);
    Get_Gain_Matrix(&gain_LQR); // Set Gains
    // END CORALS CODE
}

void loop() {
    // BEGIN CORALS CODE

    TC_Run();
    CORALS::run();
    // Dynamics
    Vector<double> torqueBody_Real(3) = CORALS::computeT_Actual(thetaG, Hs, DCM_BG, omegaG);
    Vector<double> wk1 = CORALS::bodyDynamics(torqueBody_Real);
    Vector<double> q_k1 = CORALS::qPropogation(q_k, betaVector);
    // Control
    gyroModifier = CORALS::momEnvelope(target_T, real_wB, enabled);
    // Targetting Data
    qError = qTarget * qActual;
    phiError =  = 0.5 * acos(qError(4));

    // Target Generator
    int successTick = Control::TargetGen::successCounter(qError(4));
    int targetIndex = Control::TargetGen::detIndex(successTick,dt,pointTime); // Count col index, sensor data needed for dt & pointTime
    Get_Indexed_Targets(targetIndex,&currentTarget);

    // Torque
    xVector = Control::__LQR::det_xVector(qError, target_wB, actual_wB);
    targetT_LQR = Control::__LQR::LQR_detTargetT(xVector, K); 

    // Actuator
    errorCount = Control::Actuators::countPhiError(phiError,errorCount); // For use in gyroModifier
    gyroModifier = Control::Actuators::modGyros(currentTarget,actual_wB,errorCount,enabled); // Mult commanded rate by this
    commanded_wG = Control::Actuators::compute_wG(thetaG,Hs,DCM_BG,LQR_detTargetT);

    // Theta G
    thetaG_k1 = Integrators::eulerIntegrate(thetaG_k,commanded_wG,dt); 

    // Send wG to DataStore via API
    //DataStore.Set(COMMANDED_WG, &commanded_wG);
    //  Command
    for (int i = 0; i < 6; i++) {
        CORALS::cmdGimbalRate(drivers.get(i), gyroModifier*commanded_wG.get(i));
    }
    // END CORALS CODE
}

void setup_error(String message) {
    if (message.length() > 0) SERIAL_OUT_PRINTLN("RPC initialized on " + CORE_NAME + ".");
(message);

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
    if (digitalRead(LEDR) == HIGH) {
        while (true) {
            digitalWrite(LEDR, LOW);
            delay(500);
            digitalWrite(LEDR, HIGH);
            delay(500);
        }
    }
#endif // CPU_TYPE
}