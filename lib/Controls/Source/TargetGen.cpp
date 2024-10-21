/**
 ********************************************************************************
 * @file    TargetGen.cpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   Target Generator Implementation
 * @version 1.0
 * @date    2024-08-17
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __TARGETGEN_CPP__
#define __TARGETGEN_CPP__

#include <math.h>
#include "TargetGen.hpp"
#include "Matrix.tpp"
#include "Quaternion.tpp"

namespace Control {

namespace TargetGen {

const int pointTol = 5 * M_PI / 180;

class TargetGen {

    private:
        int ticker = 0; // Track phi error matches per dt
        int index = 0;
        
    public:

        int successCounter(const double& phiError) { // Use radians for inputs
            if (phiError < pointTol) {
                ticker++;
            } else {
                ticker = 0;
            }
            return ticker;
        }

        int detIndex(const int& ticker, const double& dt, const double& pointingTime) { 
            if (ticker > pointingtime / dt) { // dt constant, pointing time = time spent <= pointTol (set in init)
                ticker = 0;
                index++;
            }
            return index;
        }

/*         Quaternion<T> decideTarget(const Matrix<double>& qTargets, const int& index) {
            return qTargets.subMatrix(0, 4, index, index + 1);
        } */ // covered by api command now

}

} // End TargetGen
} // End Control

#endif // __TARGETGEN_CPP__