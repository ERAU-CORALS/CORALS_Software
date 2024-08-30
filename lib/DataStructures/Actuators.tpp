/**
 ********************************************************************************
 * @file    Actuators.tpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   Actuators Implementation
 * @version 1.0
 * @date    2024-08-21
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __ACTUATORS_TPP__
#define __ACTUATORS_TPP__

#include <math.h>
#include "BodyDynamics.tpp"
#include "Matrix.tpp"

namespace Actuators {

const int maxCount = 40; // Allows for 0.5 degree increments

template<typename T>
class Actuators {

    public:

    T countPhiError(const Matrix<T>& phiError, T counter) { // NOTE: Counter will have to be initialized to zero in main before calling this function (int counter = 0)
        int k = phiError.length() - 1; // Can change this to use computeDifference from SLFun

        if (counter >= maxCount) {
            throw std::invalid_argument( "Cannot achieve desired attitude" ); // Would be great to give user the specific attitude that cannot be achieved
        } else {
            if (phiError(k) <= phiError(k + 1)) {
                return counter + 1;
            } else {
                return 0;
            }
        }

    int modGyros(const Matrix<T>& targetT, const Matrix<T>& wB_Actual, T counter) { // Multiplier to keep gyros from producing too much momentum
        counter = countPhiError(phiError,counter);

        T thresh = maxCount - counter * M_PI / 360; // Adjust threshold by 0.5 degrees per counter increment
        Matrix<T> H_B = targetT.dot(wB_Actual);
        Matrix<T> wB_Mag = sqrt(wB_Actual.dot(wB_Actual));

        if (targetT > 0 && wB_Mag > thresh) {
            return 0;
        } else {
            return 1;
        }
    } 

    Matrix<T> compute_wG(const Matrix<T>& thetaG, const T& Hs, const Matrix<T>& DCM_BG, const Matrix<T>& targetT) {
        SLFun::Simulink::createC<T> createC;
        Matrix<T> C = createC.computeC(thetaG, Hs, DCM_BG); // cmgDynamics will become a member of SLFun
        Matrix<T> invC = C.transpose() * (C * C.transpose()).inverse();
        return invC * targetT;
    }

}

}

#endif // __ACTUATORS_TPP__