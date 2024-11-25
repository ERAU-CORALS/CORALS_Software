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

#ifndef __SLFUN_CPP__
#define __SLFUN_CPP__

#include <math.h>
#include "Vector.tpp"
#include "Matrix.tpp"

namespace SIMULINK {

    private:
        Vector<double> previous;

    public:

    SIMULINK(): previous(Vector<double>::zeros(3,1)) {} // Initialize previous value for difference

//Difference Function
    Vector<double> computeDifference(const Vector<double>& current) { // Define vector or matrix? matrix might be more inclusive
        Vector<double> diff = current - previous;
        previous = current;
        return diff;
    }

// Limit Function
    Vector<double> limitOutput(const double& upper, const double& lower, const Vector<double>& output) {
        Vector<double> limitedOutput(output.rows(), output.cols());
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
    Matrix<double> computeCn(const Vector<double>& thetaGn, const double& Hs, const Matrix<double>& DCM_BGn) {// [C_n] for each CMG
        Matrix<double> DCM_GGp(3,1); // DCM G to G'
        DCM_GGp(0,0) = 0;
        DCM_GGp(1,0) = Hs * cos(thetaGn);
        DCM_GGp(2,0) = Hs * sin(thetaGn);
        return DCM_BGn * DCM_GGp;
    }

    Matrix<double> computeC(const Vector<double>& thetaG, const double& Hs, const Matrix<double>& DCM_BG) {// [C] for all CMGs NOTE: this assumes DCM_BG is a [3x24] and could be inefficent :(
        int N = thetaG.length();
        Matrix<double> C(3,N);
        for (int i = 0; i < N; i++) {
            Matrix<double> DCM_BGn = DCM_BG.subMatrix(0, 3, i * 3, (i + 1) * 3); // Assumes DCM_BG is a [3x3*N] matrix
            Matrix<double> Cn = computeCn(thetaG(i), Hs, DCM_BGn);
            for (int j = 0; j < 3; j++) {
                C(j,i) = Cn(j,0);
            }
        }
        return C;
    }

} // End SIMULINK

#endif // __SLFUN_TPP__