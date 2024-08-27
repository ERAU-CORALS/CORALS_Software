/**
 ********************************************************************************
 * @file    Quaternion.tpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   Body Dynamics Implementation
 * @version 1.0
 * @date    2024-08-21
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __BODYDYNAMICS_TPP__
#define __BODYDYNAMICS_TPP__

#include <math.h>
#include "Matrix.tpp"

namespace Dynamics {

namespace Body {

template<typename T>
class BodyDynamics {

    public:

    Matrix<T> wEOM(const Matrix<T>& I, const Matrix<T>& T_B, const Matrix<T>& w_B) {
        return I.inverse() * (T_B - w_B.cross(I * w_B));
    }

};

} // End Body

} // End Dynamics