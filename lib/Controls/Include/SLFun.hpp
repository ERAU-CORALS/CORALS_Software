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
#include "Matrix.tpp"

namespace SIMULINK {

const int N = 6; // Number of CMGs, maybe needs to be defined within main program

class SIMULINK {

    private:
        Matrix<T> previous;

    public:

    SIMULINK(): previous(Matrix<T>::zeros(3,1)) {} // Initialize previous value for difference

    Matrix<T> computeDifference(const Matrix<T>& current)
    Matrix<T> limitOutput(const T& upper, const T& lower, const Matrix<T>& output)
    Matrix<T> computeCn(const T& thetaGn, const T& Hs, const Matrix<T>& DCM_BGn)
    Matrix<T> computeC(const Matrix<T>& thetaG, const T& Hs, const Matrix<T>& DCM_BG) 
}

}