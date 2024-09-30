/**
 ********************************************************************************
 * @file    Quaternion.tpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   Body & CMG Dynamics Implementation
 * @version 1.0
 * @date    2024-08-21
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include <math.h>
#include "List.tpp"
#include "Matrix.tpp"

namespace Dynamics {

namespace CMG {
    
class CMGDynamics {

public:

    Matrix<T> computeT_Actual(const Matrix<T>& thetaG, const T& Hs, const Matrix<T>& DCM_BG, const Matrix<T>& omegaG) {// [T] for all CMGs
    SIMULINK::SIMULINK<T> detC;
        Matrix<T> C_Prime = detC.computeC(thetaG, Hs, DCM_BG);
        return C_Prime * omegaG;
    }

}; // End CMGDynamics

} // End CMG

} // End Dynamics