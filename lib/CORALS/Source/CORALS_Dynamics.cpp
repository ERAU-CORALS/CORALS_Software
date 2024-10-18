/**
 ********************************************************************************
 * @file    CORALS_Dynamics.cpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   CORALS Dynamics Implementation
 * @version 1.0
 * @date    2024-08-21
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __CORALS_DYNAMICS_CPP__
#define __CORALS_DYNAMICS_CPP__

#include <math.h>
#include "Matrix.tpp"
#include "Vector.tpp"
#include "Quaternion.hpp"
#include "CORALS_Dynamics.hpp"

namespace CORALS {

//#ifdef GIGA_R1_M7

    Vector<double> computeT_Actual(const Matrix<double>& thetaG, const T& Hs, const Matrix<double>& DCM_BG, const Matrix<double>& omegaG) {// [T] for all CMGs
    
        SIMULINK::SIMULINK<double> detC;

        Matrix<T> C_Prime = detC.computeC(thetaG, Hs, DCM_BG);
        return C_Prime * omegaG;
    }

    Vector<double> wEOM(const Matrix<double>& MoI, const Matrix<double>& torqueBody, const Matrix<double>& wVector) {
        return MoI.inverse()*torqueBody-wVector.cross(MoI*wVector);
    }

    Vector<double> qPropogation(Vector<double> q_k, Vector<double> betaVector) {
        Vector<double> qPrime_1(4);
        Vector<double> qHat_1(3);

        qHat_1 =  betaVector.norm() * sin(betaVector.mag()/2);
        double q4_1 = cos(betaVector.mag()/2);

        for (int i = 0; i < 3; i++) {
            qPrime_1.set(i, qHat_1.get(i));
        }
        qPrime_1.set(3, q4_1);

        return Quaternion::qPrime1.oTimes(q_k);
    }

    Vector<double> bodyDynamics(const Matrix<double>& torqueBody_Real, const Matrix<double>& wk1) {

        Vector<double> wDotVector = wEOM(MoI, torqueBody_Real, wk1); // Need to change to handle wk1 recursively

        return Integrator::eulerIntegrate(wB_Vector, wDotVector, dt);
    }

    void DYN_Init() {
        
    }

    void DYN_Run() {
        Vector<double> torqueBody_Real(3) = computeT_Actual(thetaG, Hs, DCM_BG, omegaG);
        Vector<double> wk1 = bodyDynamics(torqueBody_Real);
        Vector<double> q_k1 = qPropogation(q_k, betaVector);
    }

    #else //GIGA_R1_M4
    //do nothing

    #endif // GIGA_R1_M7

}

#endif // __CORALS_DYNAMICS_CPP__