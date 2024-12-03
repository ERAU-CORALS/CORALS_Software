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

#ifdef GIGA_R1_M7

namespace CORALS {

const uint8_t Max_CMGs = 6;

class CORALS_Controller {
    using GimbalSet = DataStructures::Vector::Vector<Hardware::GimbalMotor*>;
    using SpinSet = DataStructures::Vector::Vector<Hardware::SpinMotor*>;

    public:
        CORALS_Controller(const uint8_t cmgCount);
        ~CORALS_Controller();

        void init();
        void run();

    private:
        GimbalSet m_Gimbals{Max_CMGs};
        SpinSet m_Spins{Max_CMGs};

        DMatrix m_DCM_BR{3,3};
        uint8_t m_cmgCount;
};

DVector Get_ThetaG_ICs(const uint8_t cmgCount);
DMatrix Get_DCM_RG(const uint8_t cmgCount, const uint8_t cmgIndex);

void Controller_Run();

extern CORALS_Controller Controller;

} // namespace CORALS

#endif // GIGA_R1_M7

#endif // __CORALS_CONTROLLER_HPP__