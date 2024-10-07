/**
 ********************************************************************************
 * @file    CORALS_Controller.cpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   Body Controller Implementation
 * @version 1.0
 * @date    2024-08-21
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __CORALS_CONTROLLER_CPP__
#define __CORALS_CONTROLLER_CPP__

#include <math.h>

#include "CORALS_Controller.hpp"
#include "Matrix.tpp"
#include "TargetGen.hpp"

namespace CORALS { // Begin CORALS

Matrix<double> subMatrix(Matrix<double> matrix, int startRow, int endRow, int startCol, int endCol) {

    Matrix<double> newMatrix(endRow-startRow+1,endCol-startCol+1);

    for(int i = startRow; i <= endRow; i++) {
        for(int j = startCol; j <= endCol; j++) {
            newMatrix.set(i-startRow,j-startCol,matrix.get(i,j));
        }
    }

    return newMatrix
}

Matrix<double> get_thetaGICs(int N) {

    Matrix<double> thetaGICs(N,1);

    switch(N) {
/*         case 3:
            thetaGICs = {
                {0},
                {0},
                {0}
            };
            break; */
        case 4:
            thetaGICs = {
                {-130*M_PI/180},
                {-130*M_PI/180},
                {60*M_PI/180},
                {60*M_PI/180}
            };
            break;
/*         case 5:
            thetaGICs = {
                {0},
                {0},
                {0},
                {0},
                {0}
            };
            break; */
        case 6:
            thetaGICs = {
                {-M_PI},
                {-M_PI_2},
                {-M_PI_2},
                {-M_PI},
                {-M_PI_2},
                {-M_PI_2}
            };
            break;
/*         case 7:
            thetaGICs = {
                {0},
                {0},
                {0},
                {0},
                {0},
                {0},
                {0}
            }; */
/*         case 8:
            thetaGICs = {
                {0},
                {0},
                {0},
                {0},
                {0},
                {0},
                {0},
                {0}
            };
            break; */
    }

    return thetaGICs
}

Matrix<double> getDCM_BG(int N) {

    Matrix<double> DCM_BG(3,3*N);
    Matrix<double> DCM_BR = { // zBody points down
        {cos(M_PI), 0, -sin(M_PI)},
        {0, 1, 0},
        {sin(M_PI), 0, cos(M_PI)}
    };

    Matrix<double> lvl1_DCM_RG[3][12] = { // Layer 1 Gimbals
        {cos(-3*M_PI_4)*cos(M_PI_2),sin(M_PI_2),-cos(M_PI_2)*sin(-3*M_PI_4),cos(-M_PI_4)*cos(M_PI_2),sin(M_PI_2),-cos(M_PI_2)*sin(-M_PI_4),cos(3*M_PI_4)*cos(M_PI_2),sin(M_PI_2),-cos(M_PI_2)*sin(3*M_PI_4),cos(M_PI_4)*cos(M_PI_2),sin(M_PI_2),-cos(M_PI_2)*sin(M_PI_4)},
        {-cos(-3*M_PI_4)*sin(M_PI_2),cos(M_PI_2),sin(-3*M_PI_4)*sin(M_PI_2),-cos(-M_PI_4)*sin(M_PI_2),cos(M_PI_2),sin(-M_PI_4)*sin(M_PI_2),-cos(3*M_PI_4)*sin(M_PI_2),cos(M_PI_2),sin(3*M_PI_4)*sin(M_PI_2),-cos(M_PI_4)*sin(M_PI_2),cos(M_PI_2),sin(M_PI_4)*sin(M_PI_2)},
        {sin(-3*M_PI_4),0,cos(-3*M_PI_4),sin(-M_PI_4),0,cos(-M_PI_4),sin(3*M_PI_4),0,cos(3*M_PI_4),sin(M_PI_4),0,cos(M_PI_4)}
    };
 
    Matrix<double> lvl2_DCM_RG[3][12]; // Layer 2 Gimbals
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            lvl2_DCM_RG[i][j] = lvl1_DCM_RG[i][j]; // Gimbal 5 = Gimbal 1
            lvl2_DCM_RG[i][j+3] = lvl1_DCM_RG[i][j+9]; // Gimbal 6 = Gimbal 4
            lvl2_DCM_RG[i][j+6] = lvl1_DCM_RG[i][j+3]; // Gimbal 7 = Gimbal 2
            lvl2_DCM_RG[i][j+9] = lvl1_DCM_RG[i][j+6]; // Gimbal 8 = Gimbal 3
        }
    }

    for (int k = 0, m = 0; k < N; k++) {
        Matrix<double> temp_DCM_RG1 = subMatrix(lvl1_DCM_RG,0,2,3*k,3*k+2);
        Matrix<double> temp_DCM_RG2 = subMatrix(lvl2_DCM_RG,0,2,3*k,3*k+2);
        Matrix<double> temp_DCM_BG1 = DCM_BR * temp_DCM_RG1;
        Matrix<double> temp_DCM_BG2 = DCM_BR * temp_DCM_RG2;
        for (int j = 0; j < 3; j++) {
            for (int l = 0; l < 3; l++) {
                DCM_BG.set(j,l+m,DCM_RG.get(j,l));
            }
        }
        m += 3;
    }

    return DCM
}

Matrix<double> eulerIntegrate(const Matrix<double>& x_k, const Matrix<double>& dx, double dt) {
    return x_k + dt*dx
}

void CTRL_Init() { // Assume targets generated

    Quaternion<double> qError;
    double phiError;
    Quaternion<T> currentTarget; // Get from DataStore/API
    double errorCount = 0;
    double gyroModifier = 1;
    Matrix<double> thetaG_k = get_thetaGICs(N);
    Matrix<double> commanded_wG;

    // Retrieve from API
    GainMatrix gain_LQR; // Init Gains
    TargetList *targetList = nullptr; // Init Targets
    Get_Gain_Matrx(&gain_LQR); // Set Gains
    DataStore.Get(TARGET_LIST, &targetList); // Set Targets

}

void CTRL_Run() {

    // Targetting Data
    qError = qTarget * qActual;
    phiError =  = 0.5 * acos(qError(4));

    // Target Generator
    int successTick = Control::TargetGen::successCounter(qError(4));
    int targetIndex = Control::TargetGen::detIndex(successTick,dt,pointTime); // Count col index, sensor data needed for dt & pointTime
    Quaternion<T> currentTarget = Control::TargetGen::decideTarget(qTargets,targetIndex);
 
    // Torque
    Matrix<double> xVector = Control::__LQR::det_xVector(qError, target_wB, actual_wB);
    Matrix<double> targetT_LQR = Control::__LQR::LQR_detTargetT(xVector, K); // Implement switch case for PID v LQR?

    // Theta G
    thetaG_k1 = eulerIntegrate(thetaG_k,gyroModifier,dt);

    // Actuator
    errorCount = Control::Actuators::countPhiError(phiError,errorCount);
    gyroModifier = Control::Actuators::modGyros(currentTarget,actual_wB,errorCount);
    commanded_wG = Control::Actuators::compute_wG(thetaG,Hs,DCM_BG,LQR_detTargetT);

    // Send wG to DataStore
    //DataStore.Set(COMMANDED_WG, &commanded_wG);

}

} // End CORALS
