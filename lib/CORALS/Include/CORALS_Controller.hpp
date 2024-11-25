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
#include "CORALS_Dynamics.hpp"

namespace CORALS {

    DMatrix subMatrix(DMatrix matrix, int startRow, int endRow, int startCol, int endCol);
    DMatrix get_thetaGICs(int N);
    DMatrix getDCM_BG(int N);
    DMatrix eulerIntegrate(const DMatrix& x_k, const DMatrix& dx, double dt);

}

#endif