/**
 ********************************************************************************
 * @file    CORALS_DataStore.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS DataStore Implementation
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "CORALS_DataStore.hpp"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include <Arduino.h>
#include <ArduinoBLE.h>
#include <RPC.h>

#include <List.tpp>
#include <Vector.tpp>
#include <Matrix.tpp>

#include "CORALS_BLE.inc"

namespace {

using namespace DataStructures::List;
using namespace DataStructures::Vector;

#ifdef GIGA_R1_M7

// Settings - TBD

// Gains
Matrix::Matrix<double> Gains(3, 3);
double Gain11 = 0.0;
double Gain12 = 0.0;
double Gain13 = 0.0;
double Gain21 = 0.0;
double Gain22 = 0.0;
double Gain23 = 0.0;
double Gain31 = 0.0;
double Gain32 = 0.0;
double Gain33 = 0.0;

// Targets
List<Vector<double>*> TargetQueue;

// Attitude
Vector<double> Attitude(4);

// Errors - TBD

// States
double PrimaryVoltage = 0.0;
double SecondaryVoltage = 0.0;
double SingularityParameter = 0.0;

#else // GIGA_R1_M4

// BLE Services
BLEService SettingsService(BLE_UUID_CORALS_SETTINGS_SERVICE);
BLEService GainsService(BLE_UUID_CORALS_GAINS_SERVICE);
BLEService TargetsService(BLE_UUID_CORALS_TARGETS_SERVICE);
BLEService AttitudeService(BLE_UUID_CORALS_ATTITUDE_SERVICE);
BLEService ErrorsService(BLE_UUID_CORALS_ERRORS_SERVICE);
BLEService StatesService(BLE_UUID_CORALS_STATES_SERVICE);

// BLE Settings Characteristics - TBD

// BLE Gains Characteristics
BLEDoubleCharacteristic Gain11Characteristic(BLE_UUID_CORALS_GAINS_GAIN11_CHARACTERISTIC, BLERead | BLEWrite | BLENotify);
BLEDoubleCharacteristic Gain12Characteristic(BLE_UUID_CORALS_GAINS_GAIN12_CHARACTERISTIC, BLERead | BLEWrite | BLENotify);
BLEDoubleCharacteristic Gain13Characteristic(BLE_UUID_CORALS_GAINS_GAIN13_CHARACTERISTIC, BLERead | BLEWrite | BLENotify);
BLEDoubleCharacteristic Gain21Characteristic(BLE_UUID_CORALS_GAINS_GAIN21_CHARACTERISTIC, BLERead | BLEWrite | BLENotify);
BLEDoubleCharacteristic Gain22Characteristic(BLE_UUID_CORALS_GAINS_GAIN22_CHARACTERISTIC, BLERead | BLEWrite | BLENotify);
BLEDoubleCharacteristic Gain23Characteristic(BLE_UUID_CORALS_GAINS_GAIN23_CHARACTERISTIC, BLERead | BLEWrite | BLENotify);
BLEDoubleCharacteristic Gain31Characteristic(BLE_UUID_CORALS_GAINS_GAIN31_CHARACTERISTIC, BLERead | BLEWrite | BLENotify);
BLEDoubleCharacteristic Gain32Characteristic(BLE_UUID_CORALS_GAINS_GAIN32_CHARACTERISTIC, BLERead | BLEWrite | BLENotify);
BLEDoubleCharacteristic Gain33Characteristic(BLE_UUID_CORALS_GAINS_GAIN33_CHARACTERISTIC, BLERead | BLEWrite | BLENotify);

// BLE Targets Characteristics
BLEIntCharacteristic TargetQueueIndexCharacteristic(BLE_UUID_CORALS_TARGETS_QUEUE_INDEX_CHARACTERISTIC, BLERead | BLEWrite | BLENotify);
BLECharCharacteristic TargetGetSetRemoveCharacteristic(BLE_UUID_CORALS_TARGETS_GET_SET_REMOVE_CHARACTERISTIC, BLERead | BLEWrite | BLENotify);
BLEDoubleCharacteristic TargetQ0Characteristic(BLE_UUID_CORALS_TARGETS_Q0_CHARACTERISTIC, BLERead | BLEWrite | BLENotify);
BLEDoubleCharacteristic TargetQ1Characteristic(BLE_UUID_CORALS_TARGETS_Q1_CHARACTERISTIC, BLERead | BLEWrite | BLENotify);
BLEDoubleCharacteristic TargetQ2Characteristic(BLE_UUID_CORALS_TARGETS_Q2_CHARACTERISTIC, BLERead | BLEWrite | BLENotify);
BLEDoubleCharacteristic TargetQ3Characteristic(BLE_UUID_CORALS_TARGETS_Q3_CHARACTERISTIC, BLERead | BLEWrite | BLENotify);

// BLE Attitude Characteristics
BLEDoubleCharacteristic AttitudeQ0Characteristic(BLE_UUID_CORALS_ATTITUDE_Q0_CHARACTERISTIC, BLERead | BLENotify);
BLEDoubleCharacteristic AttitudeQ1Characteristic(BLE_UUID_CORALS_ATTITUDE_Q1_CHARACTERISTIC, BLERead | BLENotify);
BLEDoubleCharacteristic AttitudeQ2Characteristic(BLE_UUID_CORALS_ATTITUDE_Q2_CHARACTERISTIC, BLERead | BLENotify);
BLEDoubleCharacteristic AttitudeQ3Characteristic(BLE_UUID_CORALS_ATTITUDE_Q3_CHARACTERISTIC, BLERead | BLENotify);

// BLE Errors Characteristics - TBD

// BLE States Characteristics
BLEDoubleCharacteristic PrimaryVoltageCharacteristic(BLE_UUID_CORALS_STATES_PRIMARY_VOLTAGE_CHARACTERISTIC, BLERead | BLENotify);
BLEDoubleCharacteristic SecondaryVoltageCharacteristic(BLE_UUID_CORALS_STATES_SECONDARY_VOLTAGE_CHARACTERISTIC, BLERead | BLENotify);
BLEDoubleCharacteristic SingularityParameterCharacteristic(BLE_UUID_CORALS_STATES_SINGULARITY_PARAMETER_CHARACTERISTIC, BLERead | BLENotify);
BLEIntCharacteristic TargetListLengthCharacteristic(BLE_UUID_CORALS_STATES_TARGET_LIST_LENGTH_CHARACTERISTIC, BLERead | BLENotify);

// BLE Devices
BLEDevice DARTS;

#endif // CPU_TYPE

bool __BLE_Initialized = false;

static bool DARTS_Connect () {
#ifdef GIGA_R1_M4
    if (!__BLE_Initialized) return false;

    DARTS = BLE.central();
    return bool(DARTS);
#else // GIGA_R1_M7
    return false;
#endif // CPU_TYPE
}

} // end namespace

namespace CORALS {

using namespace DataStructures::List;
using namespace DataStructures::Vector;

void Initialize_DataStore() {
    /**
     ********************************************************************************
     * DATASTORE INITIAL VALUES AND RPC CONFIGURATION
     ********************************************************************************
    **/

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

    // Targets
    RPC.bind("Get_Indexed_Target_Q0", Get_Indexed_Target_Q0);
    RPC.bind("Get_Indexed_Target_Q1", Get_Indexed_Target_Q1);
    RPC.bind("Get_Indexed_Target_Q2", Get_Indexed_Target_Q2);
    RPC.bind("Get_Indexed_Target_Q3", Get_Indexed_Target_Q3);
    RPC.bind("Append_New_Target", Append_New_Target);
    RPC.bind("Replace_Indexed_Target", Replace_Indexed_Target);
    RPC.bind("Remove_Current_Target", Remove_Current_Target);

    // Attitude
    RPC.bind("Get_Attitude_Q0", Get_Attitude_Q0);
    RPC.bind("Get_Attitude_Q1", Get_Attitude_Q1);
    RPC.bind("Get_Attitude_Q2", Get_Attitude_Q2);
    RPC.bind("Get_Attitude_Q3", Get_Attitude_Q3);

    Set_Attitude_Q0(0.0);
    Set_Attitude_Q1(0.0);
    Set_Attitude_Q2(0.0);
    Set_Attitude_Q3(1.0);

    // Errors - TBD

    // States
    RPC.bind("Get_Primary_Voltage", Get_Primary_Voltage);
    RPC.bind("Get_Secondary_Voltage", Get_Secondary_Voltage);
    RPC.bind("Get_Singularity_Parameter", Get_Singularity_Parameter);
    RPC.bind("Get_Target_List_Length", Get_Target_List_Length);

    RPC.bind("Set_Primary_Voltage", Set_Primary_Voltage);
    RPC.bind("Set_Secondary_Voltage", Set_Secondary_Voltage);
    RPC.bind("Set_Singularity_Parameter", Set_Singularity_Parameter);

#else // GIGA_R1_M4

    // Settings - TBD

    // Gains
    RPC.call("Set_Gain11", 0.0);
    RPC.call("Set_Gain12", 0.0);
    RPC.call("Set_Gain13", 0.0);
    RPC.call("Set_Gain21", 0.0);
    RPC.call("Set_Gain22", 0.0);
    RPC.call("Set_Gain23", 0.0);
    RPC.call("Set_Gain31", 0.0);
    RPC.call("Set_Gain32", 0.0);
    RPC.call("Set_Gain33", 0.0);

    // Targets - TBD

    // Attitude - TBD

    // Errors - TBD
#endif // CPU_TYPE

    /**
     ********************************************************************************
     * BLUETOOTH LOW ENERGY
     ********************************************************************************
    **/

#ifdef GIGA_R1_M4

    // Bluetooth Initialization
    unsigned long BLE_Start = millis();
    while (!BLE.begin() && millis() - BLE_Start < 5000) continue;
    if (!BLE.begin()) {
        Serial.println("Failed to initialize BLE.");
        abort();
    }

    // BLE Name
    BLE.setDeviceName("CORALS TARGET");
    BLE.setLocalName("CORALS TARGET LOCAL");

    // Settings Characteristics - TBD

    // Gains Characteristics
    GainsService.addCharacteristic(Gain11Characteristic);
    GainsService.addCharacteristic(Gain12Characteristic);
    GainsService.addCharacteristic(Gain13Characteristic);
    GainsService.addCharacteristic(Gain21Characteristic);
    GainsService.addCharacteristic(Gain22Characteristic);
    GainsService.addCharacteristic(Gain23Characteristic);
    GainsService.addCharacteristic(Gain31Characteristic);
    GainsService.addCharacteristic(Gain32Characteristic);
    GainsService.addCharacteristic(Gain33Characteristic);

    // Targets Characteristics
    TargetsService.addCharacteristic(TargetQueueIndexCharacteristic);
    TargetsService.addCharacteristic(TargetGetSetRemoveCharacteristic);
    TargetsService.addCharacteristic(TargetQ0Characteristic);
    TargetsService.addCharacteristic(TargetQ1Characteristic);
    TargetsService.addCharacteristic(TargetQ2Characteristic);
    TargetsService.addCharacteristic(TargetQ3Characteristic);

    // Attitude Characteristics
    AttitudeService.addCharacteristic(AttitudeQ0Characteristic);
    AttitudeService.addCharacteristic(AttitudeQ1Characteristic);
    AttitudeService.addCharacteristic(AttitudeQ2Characteristic);
    AttitudeService.addCharacteristic(AttitudeQ3Characteristic);

    // Errors Characteristics - TBD

    // States Characteristics
    StatesService.addCharacteristic(PrimaryVoltageCharacteristic);
    StatesService.addCharacteristic(SecondaryVoltageCharacteristic);
    StatesService.addCharacteristic(SingularityParameterCharacteristic);
    StatesService.addCharacteristic(TargetListLengthCharacteristic);

    // Add Services to BLE
    BLE.addService(SettingsService);
    BLE.addService(GainsService);
    BLE.addService(TargetsService);
    BLE.addService(AttitudeService);
    BLE.addService(ErrorsService);
    BLE.addService(StatesService);

    // Advertise Services
    BLE.setAdvertisedServiceUuid(BLE_UUID_CORALS_ADVERTISEMENT);

    // Start BLE
    BLE.advertise();
    __BLE_Initialized = true;
    
#endif // GIGA_R1_M4
}

void Run_DataStore() {
#ifdef GIGA_R1_M7
    if (__BLE_Initialized) {
        error("BLE initialized on wrong core.");
    }
#else // GIGA_R1_M4
    if (!__BLE_Initialized) {
        error("BLE not initialized.");
    }

    if (!DARTS_Connect() || !DARTS.connected()) return;

    // Settings - TBD

    // Gains
    RPC.call("Set_Gain11", Gain11Characteristic.value());
    RPC.call("Set_Gain12", Gain12Characteristic.value());
    RPC.call("Set_Gain13", Gain13Characteristic.value());
    RPC.call("Set_Gain21", Gain21Characteristic.value());
    RPC.call("Set_Gain22", Gain22Characteristic.value());
    RPC.call("Set_Gain23", Gain23Characteristic.value());
    RPC.call("Set_Gain31", Gain31Characteristic.value());
    RPC.call("Set_Gain32", Gain32Characteristic.value());
    RPC.call("Set_Gain33", Gain33Characteristic.value());

    // Targets - TBD


    // Targets
#endif // CPU_TYPE
}

#ifdef GIGA_R1_M7

// Settings - TBD

// Gains
double Get_Gain11() {
    return Gain11;
}
double Get_Gain12() {
    return Gain12;
}
double Get_Gain13() {
    return Gain13;
}
double Get_Gain21() {
    return Gain21;
}
double Get_Gain22() {
    return Gain22;
}
double Get_Gain23() {
    return Gain23;
}
double Get_Gain31() {
    return Gain31;
}
double Get_Gain32() {
    return Gain32;
}
double Get_Gain33() {
    return Gain33;
}

void Set_Gain11(double value) {
    Gain11 = value;
}
void Set_Gain12(double value) {
    Gain12 = value;
}
void Set_Gain13(double value) {
    Gain13 = value;
}
void Set_Gain21(double value) {
    Gain21 = value;
}
void Set_Gain22(double value) {
    Gain22 = value;
}
void Set_Gain23(double value) {
    Gain23 = value;
}
void Set_Gain31(double value) {
    Gain31 = value;
}
void Set_Gain32(double value) {
    Gain32 = value;
}
void Set_Gain33(double value) {
    Gain33 = value;
}

// Targets
double Get_Indexed_Target_Q0(ListSize_t index) {
    return TargetQueue[index]->get(0);
}
double Get_Indexed_Target_Q1(ListSize_t index) {
    return TargetQueue[index]->get(1);

}
double Get_Indexed_Target_Q2(ListSize_t index) {
    return TargetQueue[index]->get(2);
}
double Get_Indexed_Target_Q3(ListSize_t index) {
    return TargetQueue[index]->get(3);
}

void Append_New_Target(const double q0, const double q1, const double q2, const double q3) {
    Vector<double>* new_target = new Vector<double>(4);
    new_target->set(0, q0);
    new_target->set(1, q1);
    new_target->set(2, q2);
    new_target->set(3, q3);
    TargetQueue.push_back(new_target);
}
void Replace_Indexed_Target(ListSize_t index, const double q0, const double q1, const double q2, const double q3) {
    TargetQueue[index]->set(0, q0);
    TargetQueue[index]->set(1, q1);
    TargetQueue[index]->set(2, q2);
    TargetQueue[index]->set(3, q3);

}
void Remove_Current_Target() {
    delete TargetQueue.pop_front();
}

// Attitude
double Get_Attitude_Q0() {
    return Attitude.get(0);
}
double Get_Attitude_Q1() {
    return Attitude.get(1);
}
double Get_Attitude_Q2() {
    return Attitude.get(2);
}
double Get_Attitude_Q3() {
    return Attitude.get(3);
}

void Set_Attitude_Q0(double value) {
    Attitude.set(0, value);
}
void Set_Attitude_Q1(double value) {
    Attitude.set(1, value);
}
void Set_Attitude_Q2(double value) {
    Attitude.set(2, value);
}
void Set_Attitude_Q3(double value) {
    Attitude.set(3, value);
}

// Errors - TBD

// States
double Get_Primary_Voltage() {
    return PrimaryVoltage;
}
double Get_Secondary_Voltage() {
    return SecondaryVoltage;
}
double Get_Singularity_Parameter() {
    return SingularityParameter;
}
double Get_Target_List_Length() {
    return TargetQueue.size();
}

void Set_Primary_Voltage(double value) {
    PrimaryVoltage = value;
}
void Set_Secondary_Voltage(double value) {
    SecondaryVoltage = value;
}
void Set_Singularity_Parameter(double value) {
    SingularityParameter = value;
}

#endif // GIGA_R1_M7

} // end namespace CORALS