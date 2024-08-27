/**
 ********************************************************************************
 * @file    Actuators.tpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   Actuators Implementation
 * @version 1.0
 * @date    2024-08-21
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __ACTUATORS_TPP__
#define __ACTUATORS_TPP__

#include <math.h>
#include "BodyDynamics.tpp"
#include "Matrix.tpp"

namespace Actuators {

template<typename T>
class Actuators {

    public:

    T crankThresh() {

    }

    int modGyros(const Matrix<T>& targetT, const Matrix<T>& wB_Actual) { // Multiplier to keep gyros from producing too much momentum
        Matrix<T> H_B = targetT * wB_Actual;
        Matrix<T> wB_Mag = 
        if (targetT > 0.3 && wB_Mag > 0) {
            return 0;
        } else {
            return 1;
        }
    } 

    Matrix<T> compute_wG(const Matrix<T>& thetaG, const T& Hs, const Matrix<T>& DCM_BG, const Matrix<T>& targetT) {
        Dynamics::CMG::CMGDynamics<T> cmgDynamics;
        Matrix<T> C = cmgDynamics.computeC(thetaG, Hs, DCM_BG); // cmgDynamics will become a member of SLFun
        Matrix<T> invC = C.transpose() * (C * C.transpose()).inverse();
        return invC * targetT;
    }

}

}
