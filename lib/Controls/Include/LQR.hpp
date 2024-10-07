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
#include "Matrix.tpp"

namespace Control {

namespace __LQR {

    public:

    Matrix<double> det_xVector(const Quaternion<double>& qError, const Matrix<double>& target_wB, const Matrix<double>& actual_wB)
    Matrix<double> detTargetT(const Matrix<double>& xVector, const Matrix<double>& K)

} // end namespace __LQR

} // end namespace ControlSystems