/**
 ********************************************************************************
 * @file    CORALS_DataStore.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS DataStore Implementation
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __CORALS_DATASTORE_HPP__
#define __CORALS_DATASTORE_HPP__

#include <List.tpp>
#include <Vector.tpp>

namespace CORALS {

using namespace DataStructures::List;
using namespace DataStructures::Vector;

void Initialize_DataStore();
void Run_DataStore();

#ifdef GIGA_R1_M7
// Settings - TBD

// Gains
double Get_Gain11();
double Get_Gain12();
double Get_Gain13();
double Get_Gain21();
double Get_Gain22();
double Get_Gain23();
double Get_Gain31();
double Get_Gain32();
double Get_Gain33();

void Set_Gain11(const double value);
void Set_Gain12(const double value);
void Set_Gain13(const double value);
void Set_Gain21(const double value);
void Set_Gain22(const double value);
void Set_Gain23(const double value);
void Set_Gain31(const double value);
void Set_Gain32(const double value);
void Set_Gain33(const double value);

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

// Errors - TBD

// States
void Get_Primary_Voltage(double &value);
void Get_Secondary_Voltage(double &value);
void Get_Singularity_Parameter(double &value);
void Get_Target_List_Length(int &value);

void Set_Primary_Voltage(const double value);
void Set_Secondary_Voltage(const double value);
void Set_Singularity_Parameter(const double value);

#endif // GIGA_R1_M7

} // end namespace CORALS

#endif // __CORALS_DATASTORE_HPP__