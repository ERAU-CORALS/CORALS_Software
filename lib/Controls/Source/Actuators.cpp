/**
 ********************************************************************************
 * @file    Actuators.cpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   Actuator Source
 * @version 1.0
 * @date    2024-08-21
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __ACTUATORS_CPP__
#define __ACTUATORS_CPP__

#include <math.h>
#include "Actuators.hpp"
#include "Vector.tpp"

namespace Control {

namespace Actuators {
    
    int countPhiError(const Vector<double>& phiError, int counter) { // NOTE: Counter will have to be initialized to zero in main before calling this function (int counter = 0)
        int k = phiError.length() - 1; // Can change this to use computeDifference from SLFun
        int maxCount = 40; // Allows for 0.5 degree increments

        if (counter >= maxCount) {
            throw std::invalid_argument( "Cannot achieve desired attitude" ); // Replace w/ telecom error code
        } else {
            if (phiError(k) <= phiError(k + 1)) {
                return counter + 1;
            } else {
                return 0;
            }
        }

    int modGyros(const Vector<double>& targetT, const Vector<double>& wB_Actual, int counter) { // Multiplier to keep gyros from producing too much momentum
        counter = countPhiError(phiError,counter);

        T thresh = maxCount - counter * M_PI / 360; // Adjust threshold by 0.5 degrees per counter increment
        Vector<double> H_B = targetT.dot(wB_Actual);
        int wB_Mag = sqrt(wB_Actual.dot(wB_Actual));

        if (targetT > 0 && wB_Mag > thresh) {
            return 0;
        } else {
            return 1;
        }
    } 

    Vector<double> compute_wG(const Matrix<double>& thetaG, const double& Hs, const Matrix<double>& DCM_BG, const Matrix<double>& targetT) {
        SLFun::Simulink::createC<double> createC;
        Matrix<double> C = createC.computeC(thetaG, Hs, DCM_BG); // cmgDynamics will become a member of SLFun
        Matrix<double> invC = C.transpose() * (C * C.transpose()).inverse();
        return invC * targetT;
    }

} // End Actuators
} // End Control

#endif // __ACTUATORS_CPP__