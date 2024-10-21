/**
 ********************************************************************************
 * @file    LQR.hpp
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
#include "Vector.tpp"
#include "Matrix.tpp"

namespace Control {

namespace __LQR {

    Vector<double> det_xVector(const Quaternion<double>& qError, const Vector<double>& target_wB, const Vector<double>& actual_wB);
    Vector<double> LQR_detTargetT(const Vector<double>& xVector, const Matrix<double>& K);

} // end namespace __LQR

} // end namespace Control

#endif // __LQR_HPP__