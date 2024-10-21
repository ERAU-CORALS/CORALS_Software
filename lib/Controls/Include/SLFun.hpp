/**
 ********************************************************************************
 * @file    SLFun.tpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   SIMULINK Function Headers
 * @version 1.0
 * @date    2024-08-21
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __SLFUN_HPP__
#define __SLFUN_HPP__

#include <math.h>
#include "Vector.tpp"
#include "Matrix.tpp"

namespace SIMULINK {

class SIMULINK {

    private:
        Vector<double> previous;

    public:

    SIMULINK(): previous(Vector<double>::zeros(3,1)) {} // Initialize previous value for difference

    Vector<double> computeDifference(const Matrix<double>& current)
    Vector<double> limitOutput(const double& upper, const double& lower, const Matrix<double>& output)
    Matrix<double> computeCn(const double& thetaGn, const double& Hs, const Matrix<double>& DCM_BGn)
    Matrix<double> computeC(const Vector<double>& thetaG, const double& Hs, const Matrix<double>& DCM_BG) 
}

}

#endif // __SLFUN_HPP__