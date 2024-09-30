/**
 ********************************************************************************
 * @file    TargetGen.tpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   Target Generator Implementation
 * @version 1.0
 * @date    2024-08-17
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __TARGETGEN_TPP__
#define __TARGETGEN_TPP__

#include <math.h>
#include "Matrix.tpp"
#include "Quaternion.tpp"

namespace TargetGen {

const int pointTol = 5 * M_PI / 180;

class TargetGen {

    private:
        int ticker = 0; // Track phi error matches per dt
        int index = 0;
        
    public:

        int successCounter(const T& phiError) { // Use radians for inputs
            if (phiError < pointTol) {
                ticker++;
            } else {
                ticker = 0;
            }
            return ticker;
        }

        int detIndex(const T& ticker, const T& dt, const T& pointingTime) { 
            if (ticker > pointingtime / dt) { // dt constant, pointing time = time spent <= pointTol (set in init)
                ticker = 0;
                index++;
            }
            return index;
        }

        Quaternion<T> decideTarget(const Matrix<T>& qTargets, const int& index) {
            return qTargets.subMatrix(0, 4, index, index + 1);
        }

}

} // End TargetGen