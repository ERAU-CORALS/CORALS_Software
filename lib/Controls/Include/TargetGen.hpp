/**
 ********************************************************************************
 * @file    TargetGen.tpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   Target Generator Headers
 * @version 1.0
 * @date    2024-08-17
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __TARGETGEN_HPP__
#define __TARGETGEN_HPP__

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

        int successCounter(const T& phiError) 
        int detIndex(const T& ticker, const T& dt, const T& pointingTime)
        Quaternion<T> decision(const Matrix<T>& qTargets, const int& index)
        
}

} // End TargetGen