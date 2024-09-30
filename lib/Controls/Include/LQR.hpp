/**
 ********************************************************************************
 * @file    LQR.tpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   Linear Quadratic Regulator Controller Headers
 * @version 1.0
 * @date    2024-08-17
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __LQR_HPP__
#define __LQR_HPP__

#include <math.h>

namespace Control {

namespace __LQR {

    public:

    Matrix<T> det_xVector(const Quaternion<T>& qError, const Matrix<T>& target_wB, const Matrix<T>& actual_wB)
    Matrix<T> detTargetT(const Matrix<T>& xVector, const Matrix<T>& K)

} // end namespace __LQR

} // end namespace ControlSystems