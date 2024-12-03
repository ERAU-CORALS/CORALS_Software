/**
 ********************************************************************************
 * @file    CORALS_API.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS Commands API
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "CORALS_API.hpp"
#include "CORALS_Configuration.hpp"

#include <ArduinoBLE.h>
#include <RPC.h>

#include "CORALS_DataStore.hpp"

#include "Internal/CORALS_BLE.inc"

namespace CORALS {

void API_Init() {
    CORALS_OUT_PRINTLN("Initializing CORALS API...");

#ifdef GIGA_R1_M7
    
    // Settings - TBD

    // Gains
    RPC.bind("Get_Gain11", Get_Gain11);
    RPC.bind("Get_Gain12", Get_Gain12);
    RPC.bind("Get_Gain13", Get_Gain13);
    RPC.bind("Get_Gain21", Get_Gain21);
    RPC.bind("Get_Gain22", Get_Gain22);
    RPC.bind("Get_Gain23", Get_Gain23);
    RPC.bind("Get_Gain31", Get_Gain31);
    RPC.bind("Get_Gain32", Get_Gain32);
    RPC.bind("Get_Gain33", Get_Gain33);

    RPC.bind("Set_Gain11", Set_Gain11);
    RPC.bind("Set_Gain12", Set_Gain12);
    RPC.bind("Set_Gain13", Set_Gain13);
    RPC.bind("Set_Gain21", Set_Gain21);
    RPC.bind("Set_Gain22", Set_Gain22);
    RPC.bind("Set_Gain23", Set_Gain23);
    RPC.bind("Set_Gain31", Set_Gain31);
    RPC.bind("Set_Gain32", Set_Gain32);
    RPC.bind("Set_Gain33", Set_Gain33);

    Set_Gain11(0.0);
    Set_Gain12(0.0);
    Set_Gain13(0.0);
    Set_Gain21(0.0);
    Set_Gain22(0.0);
    Set_Gain23(0.0);
    Set_Gain31(0.0);
    Set_Gain32(0.0);
    Set_Gain33(0.0);

    // Targets
    RPC.bind("Get_Indexed_Target_Q0", Get_Indexed_Target_Q0);
    RPC.bind("Get_Indexed_Target_Q1", Get_Indexed_Target_Q1);
    RPC.bind("Get_Indexed_Target_Q2", Get_Indexed_Target_Q2);
    RPC.bind("Get_Indexed_Target_Q3", Get_Indexed_Target_Q3);

    RPC.bind("Prepend_New_Target", Prepend_New_Target);
    RPC.bind("Append_New_Target", Append_New_Target);

    RPC.bind("Remove_First_Target", Remove_First_Target);
    RPC.bind("Remove_Last_Target", Remove_Last_Target);
    RPC.bind("Replace_Indexed_Target", Replace_Indexed_Target);

    RPC.bind("Clear_Target_List", Clear_Target_List);

    // Attitude
    RPC.bind("Get_Attitude_Q0", Get_Attitude_Q0);
    RPC.bind("Get_Attitude_Q1", Get_Attitude_Q1);
    RPC.bind("Get_Attitude_Q2", Get_Attitude_Q2);
    RPC.bind("Get_Attitude_Q3", Get_Attitude_Q3);

    Set_Attitude_Q0(0.0);
    Set_Attitude_Q1(0.0);
    Set_Attitude_Q2(0.0);
    Set_Attitude_Q3(0.0);

    // Gimbal Rates
    DVector ZeroVector(3);
    Set_Gimbal_Rates(&ZeroVector);

    // Errors - TBD

    // States
    RPC.bind("Get_Primary_Voltage", Get_Primary_Voltage);
    RPC.bind("Get_Secondary_Voltage", Get_Secondary_Voltage);
    RPC.bind("Get_Singularity_Parameter", Get_Singularity_Parameter);
    RPC.bind("Get_Target_List_Length", Get_Target_List_Length);

    Set_Primary_Voltage(0.0);
    Set_Secondary_Voltage(0.0);
    Set_Singularity_Parameter(0.0);

#else // GIGA_R1_M4

    // DO NOTHING ON M4

#endif // CORE_TYPE

    CORALS_OUT_PRINTLN("CORALS API Initialized.");
}

#ifdef GIGA_R1_M7

// Settings - TBD

// Gains
void Get_Gain_Matrix(GainMatrix *const Gain_Matrix) {
    GainMatrix *GainMatrixLocal = nullptr;
    DataStore.Get(GAIN_MATRIX, &GainMatrixLocal);
    memcpy(Gain_Matrix, GainMatrixLocal, sizeof(GainMatrix));
}

// Targets
void Get_Indexed_Target(const ListSize_t index, Quaternion *const Target) {
    TargetList *TargetsLocal = nullptr;
    DataStore.Get(TARGET_LIST, &TargetsLocal);
    memcpy(Target, (*TargetsLocal)[index], sizeof(Quaternion));
}

// Attitude
void Get_Attitude(Quaternion *const attitude) {
    Quaternion *AttitudeLocal = nullptr;
    DataStore.Get(ATTITUDE_QUATERNION, &AttitudeLocal);
    memcpy(attitude, AttitudeLocal, sizeof(Quaternion));
}

void Set_Attitude(const Quaternion *const attitude) {
    Quaternion *AttitudeLocal = nullptr;
    DataStore.Get(ATTITUDE_QUATERNION, &AttitudeLocal);
    delete AttitudeLocal;
    AttitudeLocal = new Quaternion(*attitude);
    DataStore.Set(ATTITUDE_QUATERNION, AttitudeLocal);
}

// Errors - TBD

// States
void Set_Primary_Voltage(const double voltage) {
    DataStore.Set(PRIMARY_VOLTAGE, &voltage);
}

void Set_Secondary_Voltage(const double voltage) {
    DataStore.Set(SECONDARY_VOLTAGE, &voltage);
}

void Set_Singularity_Parameter(const double parameter) {
    DataStore.Set(SINGULARITY_PARAMETER, &parameter);
}

#endif // GIGA_R1_M7
// ALL CORES BELOW:

// Settings - TBD

// Gains
void Get_Gain11(double &gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    gain = Gain_Matrix.get(0, 0);
}

void Get_Gain12(double &gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    gain = Gain_Matrix.get(0, 1);
}

void Get_Gain13(double &gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    gain = Gain_Matrix.get(0, 2);
}

void Get_Gain21(double &gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    gain = Gain_Matrix.get(1, 0);
}

void Get_Gain22(double &gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    gain = Gain_Matrix.get(1, 1);
}

void Get_Gain23(double &gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    gain = Gain_Matrix.get(1, 2);
}

void Get_Gain31(double &gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    gain = Gain_Matrix.get(2, 0);
}

void Get_Gain32(double &gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    gain = Gain_Matrix.get(2, 1);
}

void Get_Gain33(double &gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    gain = Gain_Matrix.get(2, 2);
}

void Set_Gain11(const double gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    Gain_Matrix.set(0, 0, gain);
    DataStore.Set(GAIN_MATRIX, &Gain_Matrix);
}

void Set_Gain12(const double gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    Gain_Matrix.set(0, 1, gain);
    DataStore.Set(GAIN_MATRIX, &Gain_Matrix);
}

void Set_Gain13(const double gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    Gain_Matrix.set(0, 2, gain);
    DataStore.Set(GAIN_MATRIX, &Gain_Matrix);
}

void Set_Gain21(const double gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    Gain_Matrix.set(1, 0, gain);
    DataStore.Set(GAIN_MATRIX, &Gain_Matrix);
}

void Set_Gain22(const double gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    Gain_Matrix.set(1, 1, gain);
    DataStore.Set(GAIN_MATRIX, &Gain_Matrix);
}

void Set_Gain23(const double gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    Gain_Matrix.set(1, 2, gain);
    DataStore.Set(GAIN_MATRIX, &Gain_Matrix);
}

void Set_Gain31(const double gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    Gain_Matrix.set(2, 0, gain);
    DataStore.Set(GAIN_MATRIX, &Gain_Matrix);
}

void Set_Gain32(const double gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    Gain_Matrix.set(2, 1, gain);
    DataStore.Set(GAIN_MATRIX, &Gain_Matrix);
}

void Set_Gain33(const double gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    Gain_Matrix.set(2, 2, gain);
    DataStore.Set(GAIN_MATRIX, &Gain_Matrix);
}

// Targets

void Get_Indexed_Target_Q0(const ListSize_t index, double &value) {
    TargetList *Targets = nullptr;
    DataStore.Get(TARGET_LIST, &Targets);
    value = (*Targets)[index]->get(0);
}

void Get_Indexed_Target_Q1(const ListSize_t index, double &value) {
    TargetList *Targets = nullptr;
    DataStore.Get(TARGET_LIST, &Targets);
    value = (*Targets)[index]->get(1);
}

void Get_Indexed_Target_Q2(const ListSize_t index, double &value) {
    TargetList *Targets = nullptr;
    DataStore.Get(TARGET_LIST, &Targets);
    value = (*Targets)[index]->get(2);
}

void Get_Indexed_Target_Q3(const ListSize_t index, double &value) {
    TargetList *Targets = nullptr;
    DataStore.Get(TARGET_LIST, &Targets);
    value = (*Targets)[index]->get(3);
}

void Prepend_New_Target(const double q0, 
                        const double q1, 
                        const double q2, 
                        const double q3) {
    TargetList *Targets = nullptr;
    DataStore.Get(TARGET_LIST, &Targets);
    Quaternion *Target = new Quaternion;
    Target->set(0, q0);
    Target->set(1, q1);
    Target->set(2, q2);
    Target->set(3, q3);
    Targets->push_front(Target);
}

void Append_New_Target(const double q0, 
                       const double q1, 
                       const double q2, 
                       const double q3) {
    TargetList *Targets = nullptr;
    DataStore.Get(TARGET_LIST, &Targets);
    Quaternion *Target = new Quaternion;
    Target->set(0, q0);
    Target->set(1, q1);
    Target->set(2, q2);
    Target->set(3, q3);
    Targets->push_back(Target);
}

void Remove_First_Target() {
    TargetList *Targets = nullptr;
    DataStore.Get(TARGET_LIST, &Targets);
    Targets->pop_front();
}

void Remove_Last_Target() {
    TargetList *Targets = nullptr;
    DataStore.Get(TARGET_LIST, &Targets);
    Targets->pop_back();
}

void Replace_Indexed_Target(const ListSize_t index, const double q0, 
                                                    const double q1, 
                                                    const double q2, 
                                                    const double q3) {
    TargetList *Targets = nullptr;
    DataStore.Get(TARGET_LIST, &Targets);
    Quaternion *Target = new Quaternion;
    Target->set(0, q0);
    Target->set(1, q1);
    Target->set(2, q2);
    Target->set(3, q3);
    (*Targets)[index] = Target;
}

void Clear_Target_List() {
    TargetList *Targets = nullptr;
    DataStore.Get(TARGET_LIST, &Targets);
    delete Targets;
    Targets = new TargetList;
}

// Attitude

void Get_Attitude_Q0(double &value) {
    Quaternion Attitude;
    DataStore.Get(ATTITUDE_QUATERNION, &Attitude);
    value = Attitude.get(0);
}

void Get_Attitude_Q1(double &value) {
    Quaternion Attitude;
    DataStore.Get(ATTITUDE_QUATERNION, &Attitude);
    value = Attitude.get(1);
}

void Get_Attitude_Q2(double &value) {
    Quaternion Attitude;
    DataStore.Get(ATTITUDE_QUATERNION, &Attitude);
    value = Attitude.get(2);
}

void Get_Attitude_Q3(double &value) {
    Quaternion Attitude;
    DataStore.Get(ATTITUDE_QUATERNION, &Attitude);
    value = Attitude.get(3);
}

void Set_Attitude_Q0(const double value) {
    Quaternion Attitude;
    DataStore.Get(ATTITUDE_QUATERNION, &Attitude);
    Attitude.set(0, value);
    DataStore.Set(ATTITUDE_QUATERNION, &Attitude);
}

void Set_Attitude_Q1(const double value) {
    Quaternion Attitude;
    DataStore.Get(ATTITUDE_QUATERNION, &Attitude);
    Attitude.set(1, value);
    DataStore.Set(ATTITUDE_QUATERNION, &Attitude);
}

void Set_Attitude_Q2(const double value) {
    Quaternion Attitude;
    DataStore.Get(ATTITUDE_QUATERNION, &Attitude);
    Attitude.set(2, value);
    DataStore.Set(ATTITUDE_QUATERNION, &Attitude);
}

void Set_Attitude_Q3(const double value) {
    Quaternion Attitude;
    DataStore.Get(ATTITUDE_QUATERNION, &Attitude);
    Attitude.set(3, value);
    DataStore.Set(ATTITUDE_QUATERNION, &Attitude);
}

// Gimbal Rates
void Get_Gimbal_Rates(DVector *const data) {
    DVector* gimbalRates;
    DataStore.Get(GIMBAL_RATES, &gimbalRates);
    memcpy(data, gimbalRates, sizeof(DVector));
}

void Set_Gimbal_Rates(const DVector *const data) {
    DVector* GimbalRatesLocal = nullptr;
    DataStore.Get(GIMBAL_RATES, &GimbalRatesLocal);
    delete GimbalRatesLocal;
    GimbalRatesLocal = new DVector(*data);
    DataStore.Set(GIMBAL_RATES, GimbalRatesLocal);
}

// Errors - TBD

// States

void Get_Primary_Voltage(double &voltage) {
    DataStore.Get(PRIMARY_VOLTAGE, &voltage);
}

void Get_Secondary_Voltage(double &voltage) {
    DataStore.Get(SECONDARY_VOLTAGE, &voltage);
}

void Get_Singularity_Parameter(double &parameter) {
    DataStore.Get(SINGULARITY_PARAMETER, &parameter);
}

void Get_Target_List_Length(ListSize_t &length) {
    TargetList *Targets = nullptr;
    DataStore.Get(TARGET_LIST, &Targets);
    length = Targets->size();
}

} // end namespace CORALS