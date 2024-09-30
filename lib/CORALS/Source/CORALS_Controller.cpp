/**
 ********************************************************************************
 * @file    Quaternion.tpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   Body Controller Implementation
 * @version 1.0
 * @date    2024-08-21
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "CORALS_Controller.hpp"
#include "TargetGen.hpp"

namespace CORALS { // Begin CORALS

void CTRL_Init() { // Assume targets generated

    // DataStructures::Matrix::Matrix<double> DCM_BG.readDCM_BG(); // Initialize DCM from DatStore? DCM constant, store somewhere, maybe here
    // Get_Attitude_QN... // Get target list from API
    Quaternion<double> qError;
    double phiError;
    Quaternion<T> currentTarget;
    double errorCount = 0;
    double gyroModifier = 1;
    Matrix<double> commanded_wG;

}

void CTRL_Run() {

    // Targetting Data
    qError = qTarget * qActual;
    phiError =  = 0.5 * acos(qError(4));

    // Target Generator
    int successTick = successCounter(qError(4));
    int targetIndex = detIndex(successTick,dt,pointTime); // Count col index, sensor data needed for dt & pointTime
    Quaternion<T> currentTarget = decideTarget(qTargets,targetIndex);

    // Torque
    det_xVector(qError, target_wB, actual_wB);
    Matrix<double> LQR_detTargetT(xVector, K); // Implement switch case for PID v LQR?

    // Theta G
    // Test RK4 v Euler integration

    // Actuator
    errorCount = countPhiError(phiError,errorCount);
    gyroModifier = modGyros(currentTarget,actual_wB,errorCount);
    commanded_wG = compute_wG(thetaG,Hs,DCM_BG,LQR_detTargetT);

    // Send wG to DataStore

}

} // End CORALS
