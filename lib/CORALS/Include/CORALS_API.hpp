/**
 ********************************************************************************
 * @file    CORALS_API.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS Commands API
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __CORALS_API_HPP__
#define __CORALS_API_HPP__

#include "CORALS_Configuration.hpp"
#include "CORALS_DataStore.hpp"

namespace CORALS {

using DataStructures::List::ListSize_t;

void API_Init();
void API_Loop();

#ifdef GIGA_R1_M7

// Settings - TBD

// Gains
void Get_Gain_Matrix(GainMatrix *const Gain_Matrix);

// Targets
void Get_Indexed_Target(const ListSize_t index, Quaternion *const Target);

// Attitude
void Get_Attitude(Quaternion *const attitude);
void Set_Attitude(const Quaternion *const attitude);

// Errors - TBD

// States
void Set_Primary_Voltage(const double voltage);
void Set_Secondary_Voltage(const double voltage);
void Set_Singularity_Parameter(const double parameter);

#endif // GIGA_R1_M7
// ALL CORES BELOW:

// Settings - TBD

// Gains
void Get_Gain11(double &gain);
void Get_Gain12(double &gain);
void Get_Gain13(double &gain);
void Get_Gain21(double &gain);
void Get_Gain22(double &gain);
void Get_Gain23(double &gain);
void Get_Gain31(double &gain);
void Get_Gain32(double &gain);
void Get_Gain33(double &gain);

void Set_Gain11(const double gain);
void Set_Gain12(const double gain);
void Set_Gain13(const double gain);
void Set_Gain21(const double gain);
void Set_Gain22(const double gain);
void Set_Gain23(const double gain);
void Set_Gain31(const double gain);
void Set_Gain32(const double gain);
void Set_Gain33(const double gain);

// Targets
void Get_Indexed_Target_Q0(const ListSize_t index, double &value);
void Get_Indexed_Target_Q1(const ListSize_t index, double &value);
void Get_Indexed_Target_Q2(const ListSize_t index, double &value);
void Get_Indexed_Target_Q3(const ListSize_t index, double &value);

void Prepend_New_Target(const double q0, 
                        const double q1, 
                        const double q2, 
                        const double q3);
void Append_New_Target(const double q0, 
                       const double q1, 
                       const double q2, 
                       const double q3);

void Remove_First_Target();
void Remove_Last_Target();
void Replace_Indexed_Target(const ListSize_t index, const double q0, 
                                                    const double q1, 
                                                    const double q2, 
                                                    const double q3);

void Clear_Target_List();

// Attitude
void Get_Attitude_Q0(double &value);
void Get_Attitude_Q1(double &value);
void Get_Attitude_Q2(double &value);
void Get_Attitude_Q3(double &value);

void Set_Attitude_Q0(const double value);
void Set_Attitude_Q1(const double value);
void Set_Attitude_Q2(const double value);
void Set_Attitude_Q3(const double value);

void Get_Gimbal_Rates(DVector *const data);
void Set_Gimbal_Rates(const DVector *const data);

// Errors - TBD

// States
void Get_Primary_Voltage(double &value);
void Get_Secondary_Voltage(double &value);
void Get_Singularity_Parameter(double &value);
void Get_Target_List_Length(int &value);

// Rates

} // namespace CORALS

#endif // __CORALS_API_HPP__