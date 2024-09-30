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

namespace Control {

namespace __LQR {

    Matrix<T> det_xVector(const Quaternion<T>& qError, const Matrix<T>& target_wB, const Matrix<T>& actual_wB) {
        Matrix<> wB_Error = target_wB - actual_wB;
        return Matrix<T>(qError.x, qError.y, qError.z, wB_Error(0,0), wB_Error(1,0), wB_Error(2,0));
    }

    Matrix<T> LQR_detTargetT(const Matrix<T>& xVector, const Matrix<T>& K) { // Could include ricatti silver w/ mit license
        return -K * xVector;
    }

} // end namespace __LQR

} // end namespace ControlSystems