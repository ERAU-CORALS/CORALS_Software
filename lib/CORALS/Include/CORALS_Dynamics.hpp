/**
 ********************************************************************************
 * @file    CORALS_Dynamics.hpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   CORALS Dynamics Implementation
 * @version 1.0
 * @date    2024-08-21
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __CORALS_DYNAMICS_HPP__
#define __CORALS_DYNAMICS_HPP__

#include "Matrix.tpp"
#include "Vector.tpp"

namespace CORALS {

    using DMatrix = ::DataStructures::Matrix::Matrix<double>;
    using DVector = ::DataStructures::Vector::Vector<double>;

    DMatrix computeT_Actual(const DMatrix& thetaG, const double& Hs, const DMatrix& DCM_BG, const DMatrix& omegaG);
    DMatrix wEOM(const DMatrix& MoI, const DMatrix& torqueBody, const DMatrix& wVector);
    DVector qPropogation(DVector q_k, DVector betaVector);
    DMatrix bodyDynamics(const DMatrix& torqueBody, const DMatrix& wk1);
    
}

#endif