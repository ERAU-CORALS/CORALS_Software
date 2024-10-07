/**
 ********************************************************************************
 * @file    CORALS_Controller.hpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   CORALS Controller Headers
 * @version 1.0
 * @date    2024-08-21
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __CORALS_CONTROLLER_HPP__
#define __CORALS_CONTROLLER_HPP__

#include <math.h>
#include "Matrix.tpp"

namespace CORALS {

    Matrix<double> subMatrix(Matrix<double> matrix, int startRow, int endRow, int startCol, int endCol);
    Matrix<double> get_thetaGICs(int N);
    Matrix<double> getDCM_BG(int N);
    Matrix<double> eulerIntegrate(const Matrix<double>& x_k, const Matrix<double>& dx, double dt);
    
    void CTRL_Init();
    void CTRL_Run();

}

#endif