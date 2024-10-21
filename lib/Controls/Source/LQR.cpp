/**
 ********************************************************************************
 * @file    LQR.tpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   Linear Quadratic Regulator Controller Implementation
 * @version 1.0
 * @date    2024-08-17
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __LQR_CPP__
#define __LQR_CPP__

#include <math.h>
#include "LQR.hpp"
#include "Vector.tpp"
#include "Matrix.tpp"

namespace Control {

namespace __LQR {

    Vector<double> det_xVector(const Quaternion<double>& qError, const Vector<double>& target_wB, const Vector<double>& actual_wB) {
        Vector<double> wB_Error = target_wB - actual_wB;
        return Vector<double>(qError.x, qError.y, qError.z, wB_Error(0,0), wB_Error(1,0), wB_Error(2,0));
    }

    Vector<double> LQR_detTargetT(const Vector<double>& xVector, const Matrix<double>& K) { // Could include ricatti solver?
        return -K * xVector; // Ensure K is correct size
    }

} // end namespace __LQR

} // end namespace Control

#endif