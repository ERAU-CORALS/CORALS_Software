/**
 ********************************************************************************
 * @file    Actuators.hpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   Actuators Header
 * @version 1.0
 * @date    2024-08-21
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __ACTUATORS_HPP__
#define __ACTUATORS_HPP__

#include <math.h>
#include "Matrix.tpp"

namespace Actuators {

class Actuators {

    int countPhiError(const Vector<double>& phiError, int counter) { // NOTE: Counter will have to be initialized to zero in main before calling this function (int counter = 0)
    int modGyros(const Vector<double>& targetT, const Vector<double>& wB_Actual, int counter) 
    Vector<double> compute_wG(const Vector<double>& thetaG, const double& Hs, const Matrix<double>& DCM_BG, const Matrix<double>& targetT) // DCM_BG Constant, where to define

}

}

#endif // __ACTUATORS_TPP__