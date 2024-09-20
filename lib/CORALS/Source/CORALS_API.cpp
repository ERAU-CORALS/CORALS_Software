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

void API_Loop() {
#ifdef GIGA_R1_M4
    if (!DARTS_Connect() || !DARTS.connected()) return;

    // Settings - TBD

    // Gains
    if (Gain11Characteristic.valueUpdated()) {
        RPC.call("Set_Gain11", Gain11Characteristic.value());
    }
    if (Gain12Characteristic.valueUpdated()) {
        RPC.call("Set_Gain12", Gain12Characteristic.value());
    }
    if (Gain13Characteristic.valueUpdated()) {
        RPC.call("Set_Gain13", Gain13Characteristic.value());
    }
    if (Gain21Characteristic.valueUpdated()) {
        RPC.call("Set_Gain21", Gain21Characteristic.value());
    }
    if (Gain22Characteristic.valueUpdated()) {
        RPC.call("Set_Gain22", Gain22Characteristic.value());
    }
    if (Gain23Characteristic.valueUpdated()) {
        RPC.call("Set_Gain23", Gain23Characteristic.value());
    }
    if (Gain31Characteristic.valueUpdated()) {
        RPC.call("Set_Gain31", Gain31Characteristic.value());
    }
    if (Gain32Characteristic.valueUpdated()) {
        RPC.call("Set_Gain32", Gain32Characteristic.value());
    }
    if (Gain33Characteristic.valueUpdated()) {
        RPC.call("Set_Gain33", Gain33Characteristic.value());
    }

    // Targets
    double double_buffer = 0.0;

    switch (TargetActionCharacteristic.value()) {
        case TARGET_QUEUE_NO_ACTION:
            break;
        
        case TARGET_QUEUE_GET_FRONT:

            RPC.call("Get_Indexed_Target_Q0", 0, &double_buffer);
            TargetQ0Characteristic.writeValue(double_buffer);
            
            RPC.call("Get_Indexed_Target_Q1", 0, &double_buffer);
            TargetQ1Characteristic.writeValue(double_buffer);
            
            RPC.call("Get_Indexed_Target_Q2", 0, &double_buffer);
            TargetQ2Characteristic.writeValue(double_buffer);
            
            RPC.call("Get_Indexed_Target_Q3", 0, &double_buffer);
            TargetQ3Characteristic.writeValue(double_buffer);
            
            break;

        case TARGET_QUEUE_PREPEND:

            RPC.call("Prepend_New_Target", TargetQ0Characteristic.value(), 
                                           TargetQ1Characteristic.value(), 
                                           TargetQ2Characteristic.value(), 
                                           TargetQ3Characteristic.value());

            break;

        case TARGET_QUEUE_REMOVE_FRONT:

            RPC.call("Remove_First_Target");
    
            break;

        case TARGET_QUEUE_REPLACE_FRONT:

            RPC.call("Replace_Indexed_Target", 0, TargetQ0Characteristic.value(), 
                                                  TargetQ1Characteristic.value(), 
                                                  TargetQ2Characteristic.value(), 
                                                  TargetQ3Characteristic.value());

            break;

        case TARGET_QUEUE_GET_BACK:

            RPC.call("Get_Indexed_Target_Q0", -1, &double_buffer);
            TargetQ0Characteristic.writeValue(double_buffer);
            
            RPC.call("Get_Indexed_Target_Q1", -1, &double_buffer);
            TargetQ1Characteristic.writeValue(double_buffer);
            
            RPC.call("Get_Indexed_Target_Q2", -1, &double_buffer);
            TargetQ2Characteristic.writeValue(double_buffer);
            
            RPC.call("Get_Indexed_Target_Q3", -1, &double_buffer);
            TargetQ3Characteristic.writeValue(double_buffer);
            
            break;

        case TARGET_QUEUE_APPEND:

            RPC.call("Append_New_Target", TargetQ0Characteristic.value(), 
                                          TargetQ1Characteristic.value(), 
                                          TargetQ2Characteristic.value(), 
                                          TargetQ3Characteristic.value());

            break;

        case TARGET_QUEUE_REMOVE_BACK:

            RPC.call("Remove_Last_Target");
    
            break;

        case TARGET_QUEUE_REPLACE_BACK:

            RPC.call("Replace_Indexed_Target", -1, TargetQ0Characteristic.value(), 
                                                   TargetQ1Characteristic.value(), 
                                                   TargetQ2Characteristic.value(), 
                                                   TargetQ3Characteristic.value());

            break;

        case TARGET_QUEUE_GET_INDEX:

            RPC.call("Get_Indexed_Target_Q0", TargetQueueIndexCharacteristic.value(), &double_buffer);
            TargetQ0Characteristic.writeValue(double_buffer);

            RPC.call("Get_Indexed_Target_Q1", TargetQueueIndexCharacteristic.value(), &double_buffer);
            TargetQ1Characteristic.writeValue(double_buffer);

            RPC.call("Get_Indexed_Target_Q2", TargetQueueIndexCharacteristic.value(), &double_buffer);
            TargetQ2Characteristic.writeValue(double_buffer);

            RPC.call("Get_Indexed_Target_Q3", TargetQueueIndexCharacteristic.value(), &double_buffer);
            TargetQ3Characteristic.writeValue(double_buffer);

            break;

        case TARGET_QUEUE_REPLACE_INDEX:

            RPC.call("Replace_Indexed_Target", TargetQueueIndexCharacteristic.value(), 
                                               TargetQ0Characteristic.value(), 
                                               TargetQ1Characteristic.value(), 
                                               TargetQ2Characteristic.value(), 
                                               TargetQ3Characteristic.value());

            break;

        case TARGET_QUEUE_CLEAR:

            RPC.call("Clear_Target_List");

            break;

        default:

            CORALS_DEBUG_PRINTLN("Invalid Target Queue Action.");

            break;
    }

    // Attitude
    RPC.call("Get_Attitude_Q0", &double_buffer);
    AttitudeQ0Characteristic.writeValue(double_buffer);

    RPC.call("Get_Attitude_Q1", &double_buffer);
    AttitudeQ1Characteristic.writeValue(double_buffer);

    RPC.call("Get_Attitude_Q2", &double_buffer);
    AttitudeQ2Characteristic.writeValue(double_buffer);

    RPC.call("Get_Attitude_Q3", &double_buffer);
    AttitudeQ3Characteristic.writeValue(double_buffer);

    // Errors - TBD

    // States
    RPC.call("Get_Primary_Voltage", &double_buffer);
    PrimaryVoltageCharacteristic.writeValue(double_buffer);

    RPC.call("Get_Secondary_Voltage", &double_buffer);
    SecondaryVoltageCharacteristic.writeValue(double_buffer);

    RPC.call("Get_Singularity_Parameter", &double_buffer);
    SingularityParameterCharacteristic.writeValue(double_buffer);

    int int_buffer = 0;

    RPC.call("Get_Target_List_Length", &int_buffer);
    TargetListLengthCharacteristic.writeValue(int_buffer);

#endif // CORE_TYPE
}

#ifdef GIGA_R1_M7

// Settings - TBD

// Gains
void Get_Gain_Matrix(GainMatrix *const Gain_Matrix) {
    DataStore.Get(GAIN_MATRIX, Gain_Matrix);
}

// Targets
void Get_Indexed_Target(const ListSize_t index, Quaternion *const Target) {
    TargetList Targets;
    DataStore.Get(TARGET_LIST, &Targets);
    memcpy(Target, Targets[index], sizeof(Quaternion));
}

// Attitude
void Get_Attitude(Quaternion *const attitude) {
    DataStore.Get(ATTITUDE_QUATERNION, attitude);
}

void Set_Attitude(const Quaternion *const attitude) {
    DataStore.Set(ATTITUDE_QUATERNION, attitude);
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
void Get_Gain11(double *const gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    *gain = Gain_Matrix.get(0, 0);
}

void Get_Gain12(double *const gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    *gain = Gain_Matrix.get(0, 1);
}

void Get_Gain13(double *const gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    *gain = Gain_Matrix.get(0, 2);
}

void Get_Gain21(double *const gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    *gain = Gain_Matrix.get(1, 0);
}

void Get_Gain22(double *const gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    *gain = Gain_Matrix.get(1, 1);
}

void Get_Gain23(double *const gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    *gain = Gain_Matrix.get(1, 2);
}

void Get_Gain31(double *const gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    *gain = Gain_Matrix.get(2, 0);
}

void Get_Gain32(double *const gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    *gain = Gain_Matrix.get(2, 1);
}

void Get_Gain33(double *const gain) {
    GainMatrix Gain_Matrix;
    DataStore.Get(GAIN_MATRIX, &Gain_Matrix);
    *gain = Gain_Matrix.get(2, 2);
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

void Get_Indexed_Target_Q0(const ListSize_t index, double *const value) {
    TargetList *Targets = nullptr;
    DataStore.Get(TARGET_LIST, &Targets);
    *value = (*Targets)[index]->get(0);
}

void Get_Indexed_Target_Q1(const ListSize_t index, double *const value) {
    TargetList *Targets = nullptr;
    DataStore.Get(TARGET_LIST, &Targets);
    *value = (*Targets)[index]->get(1);
}

void Get_Indexed_Target_Q2(const ListSize_t index, double *const value) {
    TargetList *Targets = nullptr;
    DataStore.Get(TARGET_LIST, &Targets);
    *value = (*Targets)[index]->get(2);
}

void Get_Indexed_Target_Q3(const ListSize_t index, double *const value) {
    TargetList *Targets = nullptr;
    DataStore.Get(TARGET_LIST, &Targets);
    *value = (*Targets)[index]->get(3);
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



} // end namespace CORALS