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

#include "Vector.tpp"

#include "CORALS_DataStructures.hpp"
#include "CORALS_Hardware.hpp"

namespace CORALS {

const uint8_t Max_CMGs = 6;

class Controller {
    using GimbalSet = DataStructures::Vector::Vector<Hardware::GimbalMotor*>;
    using SpinSet = DataStructures::Vector::Vector<Hardware::SpinMotor*>;

    public:
        Controller(const uint8_t cmgCount);
        ~Controller();

    private:
        GimbalSet m_Gimbals{Max_CMGs};
        SpinSet m_Spins{Max_CMGs};

        DMatrix *m_DCM_BG;
};

    DMatrix eulerIntegrate(const DMatrix& x_k, const DMatrix& dx, double dt);

}

#endif