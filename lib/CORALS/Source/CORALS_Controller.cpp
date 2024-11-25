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

#include <math.h>

#include "CORALS_API.hpp"
#include "CORALS_DataStore.hpp"
#include "CORALS_Controller.hpp"

#include "Quaternion.hpp"
#include "List.tpp"
#include "Matrix.tpp"
#include "TargetGen.hpp"

namespace CORALS { // Begin CORALS

#ifdef GIGA_R1_M7

Vector<double> get_thetaGICs(int N) {

    Vector<double> thetaGICs(N,1);

    switch(N) {
        case 4:
            thetaGICs = {
                {-130*M_PI/180},
                {-130*M_PI/180},
                {60*M_PI/180},
                {60*M_PI/180}
            };
            break;
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
    }

    return thetaGICs;
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

    return DCM;
}

#endif

} // End CORALS
