/**
 ********************************************************************************
 * @file    CORALS_Dynamics.hpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   CORALS Dynamics Implementation
 * @version 1.0
 * @date    2024-08-21
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __CORALS_DYNAMICS_HPP__
#define __CORALS_DYNAMICS_HPP__

#include "Matrix.tpp"

namespace CORALS {

    Matrix<double> computeT_Actual(const Matrix<double>& thetaG, const T& Hs, const Matrix<double>& DCM_BG, const Matrix<double>& omegaG);
    Matrix<double> wEOM(const Matrix<double>& MoI, const Matrix<double>& torqueBody, const Matrix<double>& wVector);
    Matrix<double> bodyDynamics(const Matrix<double>& torqueBody, const Matrix<double>& wk1);

}

#endif