/**
 ********************************************************************************
 * @file    CORALS_Dynamics.cpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   CORALS Dynamics Implementation
 * @version 1.0
 * @date    2024-08-21
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __CORALS_DYNAMICS_CPP__
#define __CORALS_DYNAMICS_CPP__

#include "CORALS_Dynamics.hpp"

namespace CORALS {

    Matrix<double> wEOM(const Matrix<double>& MoI, const Matrix<double>& torqueBody, const Matrix<double>& wVector) {
        return MoI.inverse()*torqueBody-wVector.cross(MoI*wVector);
    }

    Matrix<double> bodyDynamics(const Matrix<double>& torqueBody, const Matrix<double>& wk1) {

        Matrix<double> wDotVector = wEOM(MoI, torqueBody, wk1);

        return wVector;
    }

}

#endif // __CORALS_DYNAMICS_CPP__