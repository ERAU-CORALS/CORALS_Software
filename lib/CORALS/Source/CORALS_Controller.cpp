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

namespace CORALS { // Begin CORALS

Controller::Controller(const uint8_t cmgCount) {

    // Create Gimbal Drivers
    if (cmgCount <= 1) {
        m_Gimbals.set(0, new Hardware::GimbalMotor(CORALS_CMG_1_CS));
        m_Spins.set(0, new Hardware::SpinMotor(CORALS_CMG_1_PWM, CORALS_CMG_1_DIR, CORALS_CMG_1_INT));
    }

    if (cmgCount <= 2) {
        m_Gimbals.set(1, new Hardware::GimbalMotor(CORALS_CMG_2_CS));
        m_Spins.set(1, new Hardware::SpinMotor(CORALS_CMG_2_PWM, CORALS_CMG_2_DIR, CORALS_CMG_2_INT));
    }

    if (cmgCount <= 3) {
        m_Gimbals.set(2, new Hardware::GimbalMotor(CORALS_CMG_3_CS));
        m_Spins.set(2, new Hardware::SpinMotor(CORALS_CMG_3_PWM, CORALS_CMG_3_DIR, CORALS_CMG_3_INT));
    }

    if (cmgCount <= 4) {
        m_Gimbals.set(3, new Hardware::GimbalMotor(CORALS_CMG_4_CS));
        m_Spins.set(3, new Hardware::SpinMotor(CORALS_CMG_4_PWM, CORALS_CMG_4_DIR, CORALS_CMG_4_INT));
    }

    if (cmgCount <= 5) {
        m_Gimbals.set(4, new Hardware::GimbalMotor(CORALS_CMG_5_CS));
        m_Spins.set(4, new Hardware::SpinMotor(CORALS_CMG_5_PWM, CORALS_CMG_5_DIR, CORALS_CMG_5_INT));
    }

    if (cmgCount <= 6) {
        m_Gimbals.set(5, new Hardware::GimbalMotor(CORALS_CMG_6_CS));
        m_Spins.set(5, new Hardware::SpinMotor(CORALS_CMG_6_PWM, CORALS_CMG_6_DIR, CORALS_CMG_6_INT));
    }

    // Initialize Gimbals
    const DVector thetaG_ICs = Get_ThetaG_ICs(cmgCount);
    for (DataStructures::Vector::VectorLength_t i = 0; i < m_Gimbals.length(); i++) {
        if (m_Gimbals.get(i) != nullptr) {
            m_Gimbals.get(i)->enable_stallguard();
            m_Gimbals.get(i)->Set_ICs(thetaG_ICs.get(i));
        }
    }

    // Initialize Spinners

    // Initialize Controller
    m_DCM_BG = new DMatrix(Get_DCM_BG(cmgCount));

}

DVector Get_ThetaG_ICs(const uint8_t cmgCount) {
    DVector retval(4);
    
    switch (cmgCount) {
        case 4:
            retval.set(0, -130*M_PI/180);
            retval.set(1, -130*M_PI/180);
            retval.set(2, 60*M_PI/180);
            retval.set(3, 60*M_PI/180);
            break;

        case 6:
            retval.set(0, -M_PI);
            retval.set(1, -M_PI_2);
            retval.set(2, -M_PI_2);
            retval.set(3, -M_PI);
            retval.set(4, -M_PI_2);
            retval.set(5, -M_PI_2);
            break;

        default:
            break;
    }

    return retval;
}

DMatrix Get_DCM_BG(const uint8_t cmgCount) {
    DMatrix DCM_BG(3, 3*cmgCount);

    const DMatrix DCM_BR = {
        {cos(M_PI), 0, -sin(M_PI)},
        {0, 1, 0},
        {sin(M_PI), 0, cos(M_PI)}
    };  

    const DMatrix DCM_RG_Layer1 = {
        {cos(-3*M_PI_4)*cos(M_PI_2), sin(M_PI_2), -cos(M_PI_2)*sin(-3*M_PI_4), cos(-M_PI_4)*cos(M_PI_2), sin(M_PI_2), -cos(M_PI_2)*sin(-M_PI_4), cos(3*M_PI_4)*cos(M_PI_2), sin(M_PI_2), -cos(M_PI_2)*sin(3*M_PI_4), cos(M_PI_4)*cos(M_PI_2), sin(M_PI_2), -cos(M_PI_2)*sin(M_PI_4)},
        {-cos(-3*M_PI_4)*sin(M_PI_2), cos(M_PI_2), sin(-3*M_PI_4)*sin(M_PI_2), -cos(-M_PI_4)*sin(M_PI_2), cos(M_PI_2), sin(-M_PI_4)*sin(M_PI_2), -cos(3*M_PI_4)*sin(M_PI_2), cos(M_PI_2), sin(3*M_PI_4)*sin(M_PI_2), -cos(M_PI_4)*sin(M_PI_2), cos(M_PI_2), sin(M_PI_4)*sin(M_PI_2)},
        {sin(-3*M_PI_4), 0, cos(-3*M_PI_4), sin(-M_PI_4), 0, cos(-M_PI_4), sin(3*M_PI_4), 0, cos(3*M_PI_4), sin(M_PI_4), 0, cos(M_PI_4)}
    };

    DMatrix DCM_RG_Layer2(DCM_RG_Layer1.size());
    for (DataStructures::Matrix::MatrixLength_t i = 0; i < 3; i++) {
        for (DataStructures::Matrix::MatrixLength_t j = 0; j < 3; j++) {
            DCM_RG_Layer2.set(i, j, DCM_RG_Layer1.get(i, j)); // Gimbal 5 = Gimbal 1
            DCM_RG_Layer2.set(i, j+3, DCM_RG_Layer1.get(i, j+9)); // Gimbal 6 = Gimbal 4
            DCM_RG_Layer2.set(i, j+6, DCM_RG_Layer1.get(i, j+3)); // Gimbal 7 = Gimbal 2
            DCM_RG_Layer2.set(i, j+9, DCM_RG_Layer1.get(i, j+6)); // Gimbal 8 = Gimbal 3
        }
    }

    for (DataStructures::Matrix::MatrixLength_t k = 0, m = 0; k < cmgCount; k++, m += 3) {
        DMatrix DCM_BG_Layer = DCM_BR * DCM_RG_Layer1.submatrix(0, 2, 3*k, 3*k+2);

        if (cmgCount > 4 && k > 3) {
            DCM_BG_Layer = DCM_BR * DCM_RG_Layer2.submatrix(0, 2, 3*k, 3*k+2);
        }

        for (DataStructures::Matrix::MatrixLength_t j = 0; j < 3; j++) {
            for (DataStructures::Matrix::MatrixLength_t l = 0; l < 3; l++) {
                DCM_BG.set(j, l+m, DCM_BG_Layer.get(j, l));
            }
        }
    }

    return DCM_BG;
}

} // End CORALS
