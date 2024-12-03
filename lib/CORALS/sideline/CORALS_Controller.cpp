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
#include "CORALS_Controller.hpp"

#include "List.tpp"
#include "Matrix.tpp"

#ifdef GIGA_R1_M7

namespace CORALS { // Begin CORALS

// CORALS_Controller Controller{CORALS_CMG_COUNT};

CORALS_Controller::CORALS_Controller(const uint8_t cmgCount) {

    m_cmgCount = cmgCount;
    const double DCM_BR[3][3] = {
        {cos(M_PI), 0, -sin(M_PI)},
        {0,         1, 0        },
        {sin(M_PI), 0, cos(M_PI)}
    };
    for (DataStructures::Matrix::MatrixLength_t i = 0; i < 3; i++) {
        for (DataStructures::Matrix::MatrixLength_t j = 0; j < 3; j++) {
            m_DCM_BR.set(i, j, DCM_BR[i][j]);
        }
    }

}

void CORALS_Controller::init() {

    // Create Gimbal Drivers
    if (m_cmgCount <= 1) {
        m_Gimbals.set(0, new Hardware::GimbalMotor(CORALS_CMG_1_CS));
        m_Spins.set(0, new Hardware::SpinMotor(CORALS_CMG_1_PWM, CORALS_CMG_1_DIR, CORALS_CMG_1_INT));
    }

    if (m_cmgCount <= 2) {
        m_Gimbals.set(1, new Hardware::GimbalMotor(CORALS_CMG_2_CS));
        m_Spins.set(1, new Hardware::SpinMotor(CORALS_CMG_2_PWM, CORALS_CMG_2_DIR, CORALS_CMG_2_INT));
    }

    if (m_cmgCount <= 3) {
        m_Gimbals.set(2, new Hardware::GimbalMotor(CORALS_CMG_3_CS));
        m_Spins.set(2, new Hardware::SpinMotor(CORALS_CMG_3_PWM, CORALS_CMG_3_DIR, CORALS_CMG_3_INT));
    }

    if (m_cmgCount <= 4) {
        m_Gimbals.set(3, new Hardware::GimbalMotor(CORALS_CMG_4_CS));
        m_Spins.set(3, new Hardware::SpinMotor(CORALS_CMG_4_PWM, CORALS_CMG_4_DIR, CORALS_CMG_4_INT));
    }

    if (m_cmgCount <= 5) {
        m_Gimbals.set(4, new Hardware::GimbalMotor(CORALS_CMG_5_CS));
        m_Spins.set(4, new Hardware::SpinMotor(CORALS_CMG_5_PWM, CORALS_CMG_5_DIR, CORALS_CMG_5_INT));
    }

    if (m_cmgCount <= 6) {
        m_Gimbals.set(5, new Hardware::GimbalMotor(CORALS_CMG_6_CS));
        m_Spins.set(5, new Hardware::SpinMotor(CORALS_CMG_6_PWM, CORALS_CMG_6_DIR, CORALS_CMG_6_INT));
    }

    // Initialize Gimbals
    const DVector thetaG_ICs = Get_ThetaG_ICs(m_cmgCount);
    for (DataStructures::Vector::VectorLength_t i = 0; i < m_Gimbals.length(); i++) {
        if (m_Gimbals.get(i) != nullptr) {
            m_Gimbals.get(i)->find_home();
            m_Gimbals.get(i)->configure_coolstep();
            m_Gimbals.get(i)->Set_ICs(thetaG_ICs.get(i));
        }
    }

    // Initialize Spinners
    for (DataStructures::Vector::VectorLength_t i = 0; i < m_Spins.length(); i++) {
        if (m_Spins.get(i) != nullptr) {
            m_Spins.get(i)->Set_Speed(10000);
            m_Spins.get(i)->enableInterrupt();
        }
    }

    for (uint8_t i = 0; i < 60; i += 10) {
        SERIAL_OUT_PRINT("Delaying for ");
        SERIAL_OUT.print(60 - i);
        SERIAL_OUT.println(" more seconds...");

        delay(10000);
    }

    long set_speed = 10000;

    for (DataStructures::Vector::VectorLength_t i = 0; i < m_Spins.length(); i++) {
        if (m_Spins.get(i) != nullptr) {
            m_Spins.get(i)->Set_MaxSpeed(m_Spins.get(i)->Get_Speed().speed);
            set_speed = min(set_speed, m_Spins.get(i)->Get_MaxSpeed());
        }
    }

    for (DataStructures::Vector::VectorLength_t i = 0; i < m_Spins.length(); i++) {
        if (m_Spins.get(i) != nullptr) {
            m_Spins.get(i)->Set_Speed(set_speed);
        }
    }

    for (uint8_t i = 0; i < 60; i += 10) {
        SERIAL_OUT_PRINT("Delaying for ");
        SERIAL_OUT.print(60 - i);
        SERIAL_OUT.println(" more seconds...");

        delay(10000);
    }

    for (DataStructures::Vector::VectorLength_t i = 0; i < m_Spins.length(); i++) {
        if (m_Spins.get(i) != nullptr) {
            m_Spins.get(i)->disableInterrupt();
        }
    }
}

CORALS_Controller::~CORALS_Controller() {
    for (DataStructures::Vector::VectorLength_t i = 0; i < m_Gimbals.length(); i++) {
        if (m_Gimbals.get(i) != nullptr) {
            delete m_Gimbals.get(i);
        }
    }

    for (DataStructures::Vector::VectorLength_t i = 0; i < m_Spins.length(); i++) {
        if (m_Spins.get(i) != nullptr) {
            delete m_Spins.get(i);
        }
    }
}

void CORALS_Controller::run() {
    // Find Desired Torque
    Quaternion q_desired;
    Get_Indexed_Target(0, &q_desired);
    Quaternion q_current;
    Get_Attitude(&q_current);
    
    q_desired.set(1, -1 * q_desired.get(1));
    q_desired.set(2, -1 * q_desired.get(2));
    q_desired.set(3, -1 * q_desired.get(3));

    const Quaternion q_error = q_desired.otimes(q_current);
    DVector w_body_current(3);
    Get_Gimbal_Rates(&w_body_current);

    DVector state_vector(6);
    state_vector.set(0, q_error.get(1));
    state_vector.set(1, q_error.get(2));
    state_vector.set(2, q_error.get(3));
    state_vector.set(3, w_body_current.get(0));
    state_vector.set(4, w_body_current.get(1));
    state_vector.set(5, w_body_current.get(2));

    GainMatrix Gains;
    Get_Gain_Matrix(&Gains);

    const DVector T_desired = Gains * state_vector * -1;

    // Create C Matrix
    DMatrix C_Matrix(3,m_cmgCount);

    for (uint8_t i = 0; i < m_cmgCount; i++) {
        const float thetaG = m_Gimbals.get(i)->Get_ThetaG();
        DVector g_to_gprime(3);
        g_to_gprime.set(0, 0);
        g_to_gprime.set(1, cos(thetaG));
        g_to_gprime.set(2, sin(thetaG));
        DVector c_i = m_DCM_BR * Get_DCM_RG(m_cmgCount, i + 1) * (g_to_gprime * CORALS_GIMBAL_INERTIA * m_Spins.get(i)->Get_Speed().speed);

        C_Matrix.set(0, i, c_i.get(0));
        C_Matrix.set(1, i, c_i.get(1));
        C_Matrix.set(2, i, c_i.get(2));
    }

    const DMatrix S_Matrix = C_Matrix * C_Matrix.transpose();
    const float singularity = sq(1 - S_Matrix.determinant());

    Set_Singularity_Parameter(singularity);

    if (singularity >= CORALS_MINIMUM_SINGULARITY) {
        const DVector wg_command = C_Matrix.transpose() * S_Matrix.inverse() * T_desired;

        for (uint8_t i = 0; i < m_cmgCount; i++) {
            if (m_Gimbals.get(i) != nullptr) {
                m_Gimbals.get(i)->Set_OmegaG(constrain(wg_command.get(i), -CORALS_GIMBAL_MAX_SPEED, CORALS_GIMBAL_MAX_SPEED));
            }
        }
    }
    else {
        for (uint8_t i = 0; i < m_cmgCount; i++) {
            if (m_Gimbals.get(i) != nullptr) {
                m_Gimbals.get(i)->Set_OmegaG(0);
            }
        }
    }
}

DVector Get_ThetaG_ICs(const uint8_t cmgCount) {
    DVector retval(cmgCount);
    
    switch (cmgCount) {
        case 2:
            retval.set(0, -M_PI_2);
            retval.set(1, M_PI_2);
            break;

        case 4:
            retval.set(0, -13*M_PI/18);
            retval.set(1, -13*M_PI/18);
            retval.set(2, M_PI/3);
            retval.set(3, M_PI/3);
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

DMatrix Get_DCM_RG(const uint8_t cmgCount, const uint8_t cmg_index) {
    DMatrix DCM_RG(3, 3);

    switch (cmgCount) {
        case 4:
        case 6:
        case 8:
        default:
            switch (cmg_index) {
                case 1:
                case 2:
                case 5:
                case 7:
                    DCM_RG.set(0, 1, 1);
                    DCM_RG.set(1, 0, M_SQRT1_2);
                    DCM_RG.set(1, 2, -M_SQRT1_2);
                    DCM_RG.set(2, 0, -M_SQRT1_2);
                    DCM_RG.set(2, 2, -M_SQRT1_2);
                    break;
                
                case 3:
                case 4:
                case 6:
                case 8:
                    DCM_RG.set(0, 1, 1);
                    DCM_RG.set(1, 0, M_SQRT1_2);
                    DCM_RG.set(1, 2, M_SQRT1_2);
                    DCM_RG.set(2, 0, M_SQRT1_2);
                    DCM_RG.set(2, 2, -M_SQRT1_2);
                    break;
            }
            break;
        
        // default:
        //     break;
    }

    return DCM_RG;
}

// void Controller_Run() {
//     Controller.run();
// }

#endif // GIGA_R1_M7

} // End CORALS
