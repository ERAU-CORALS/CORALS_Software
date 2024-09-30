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

const int maxCount = 40; // Allows for 0.5 degree increments

template<typename T>
class Actuators {

    public:

    T countPhiError(const Matrix<T>& phiError, T counter) { // NOTE: Counter will have to be initialized to zero in main before calling this function (int counter = 0)
    int modGyros(const Matrix<T>& targetT, const Matrix<T>& wB_Actual, T counter) 
    Matrix<T> compute_wG(const Matrix<T>& thetaG, const T& Hs, const Matrix<T>& DCM_BG, const Matrix<T>& targetT) // DCM_BG Constant, where to define

}

}

#endif // __ACTUATORS_TPP__