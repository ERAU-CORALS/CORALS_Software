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

#include <math.h>
#include "LQR.hpp"
#include "Matrix.tpp"

namespace Control {

namespace __LQR {

    Matrix<double> det_xVector(const Quaternion<double>& qError, const Matrix<double>& target_wB, const Matrix<double>& actual_wB) {
        Matrix<> wB_Error = target_wB - actual_wB;
        return Matrix<double>(qError.x, qError.y, qError.z, wB_Error(0,0), wB_Error(1,0), wB_Error(2,0));
    }

    Matrix<double> LQR_detTargetT(const Matrix<double>& xVector, const Matrix<double>& K) { // Could include ricatti silver w/ mit license
        return -K * xVector;
    }

} // end namespace __LQR

} // end namespace ControlSystems