/**
 ********************************************************************************
 * @file    SLFun.tpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   SIMULINK Functions Implementation
 * @version 1.0
 * @date    2024-08-21
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __SLFUN_TPP__
#define __SLFUN_TPP__

#include <math.h>
#include "Matrix.tpp"

namespace SIMULINK {

class SIMULINK {

    private:
        Matrix<T> previous;

    public:

    SIMULINK(): previous(Matrix<T>::zeros(3,1)) {} // Initialize previous value for difference

//Difference Function
    Matrix<T> computeDifference(const Matrix<T>& current) {
        Matrix<T> diff = current - previous;
        previous = current;
        return diff;
    }

// Limit Function
    template<typename T>
    Matrix<T> limitOutput(const T& upper, const T& lower, const Matrix<T>& output) {
        Matrix<T> limitedOutput(output.rows(), output.cols());
        for (int i = 0; i < output.rows(); i++) {
            for (int j = 0; j < output.cols(); j++) {
                if (output(i,j) > upper) {
                    limitedOutput(i,j) = upper;
                } else if (output(i,j) < lower) {
                    limitedOutput(i,j) = lower;
                } else {
                    limitedOutput(i,j) = output(i,j);
                }
            }
        }
        return limitedOutput;
    }

// [C] Computation
        Matrix<T> computeCn(T thetaGn, const T& Hs, const Matrix<T>& DCM_BGn) {// [C_n] for each CMG
        Matrix<T> DCM_GGp(3,1); // DCM G to G'
        DCM_GGp(0,0) = 0;
        DCM_GGp(1,0) = Hs * cos(thetaGn);
        DCM_GGp(2,0) = Hs * sin(thetaGn);
        return DCM_BGn * DCM_GGp;
    }

    Matrix<T> computeC(const Matrix<T>& thetaG, const T& Hs, const Matrix<T>& DCM_BG) {// [C] for all CMGs NOTE: this assumes DCM_BG is a [3x18] and could be inefficent :(
        Matrix<T> C(3,6);
        for (int i = 0; i < 6; i++) {
            Matrix<T> DCM_BGn = DCM_BG.subMatrix(0, 3, i * 3, (i + 1) * 3);
            Matrix<T> Cn = computeCn(thetaG[i], Hs, DCM_BGn);
            for (int j = 0; j < 3; j++) {
                C(j,i) = Cn(j,0);
            }
        }
        return C;
    }

}

}