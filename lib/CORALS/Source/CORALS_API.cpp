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

#include <ArduinoBLE.h>
#include <RPC.h>

namespace CORALS {

namespace {

#ifdef GIGA_R1_M4

// BLE Services
BLEService SettingsService(BLE_UUID_CORALS_SETTINGS_SERVICE);
BLEService GainsService(BLE_UUID_CORALS_GAINS_SERVICE);
BLEService TargetsService(BLE_UUID_CORALS_TARGETS_SERVICE);
BLEService AttitudeService(BLE_UUID_CORALS_ATTITUDE_SERVICE);
BLEService ErrorsService(BLE_UUID_CORALS_ERRORS_SERVICE);
BLEService StatesService(BLE_UUID_CORALS_STATES_SERVICE);

// BLE Settings Characteristics - TBD

// BLE Gains Characteristics
BLEDoubleCharacteristic Gain11Characteristic(BLE_UUID_CORALS_GAINS_GAIN11_CHARACTERISTIC, BLEWrite);
BLEDoubleCharacteristic Gain12Characteristic(BLE_UUID_CORALS_GAINS_GAIN12_CHARACTERISTIC, BLEWrite);
BLEDoubleCharacteristic Gain13Characteristic(BLE_UUID_CORALS_GAINS_GAIN13_CHARACTERISTIC, BLEWrite);
BLEDoubleCharacteristic Gain21Characteristic(BLE_UUID_CORALS_GAINS_GAIN21_CHARACTERISTIC, BLEWrite);
BLEDoubleCharacteristic Gain22Characteristic(BLE_UUID_CORALS_GAINS_GAIN22_CHARACTERISTIC, BLEWrite);
BLEDoubleCharacteristic Gain23Characteristic(BLE_UUID_CORALS_GAINS_GAIN23_CHARACTERISTIC, BLEWrite);
BLEDoubleCharacteristic Gain31Characteristic(BLE_UUID_CORALS_GAINS_GAIN31_CHARACTERISTIC, BLEWrite);
BLEDoubleCharacteristic Gain32Characteristic(BLE_UUID_CORALS_GAINS_GAIN32_CHARACTERISTIC, BLEWrite);
BLEDoubleCharacteristic Gain33Characteristic(BLE_UUID_CORALS_GAINS_GAIN33_CHARACTERISTIC, BLEWrite);

// BLE Targets Characteristics
typedef enum __Target_Queue_Action : uint8_t {
    TARGET_QUEUE_NO_ACTION = 0x00,
    
    TARGET_QUEUE_GET_FRONT = 0x11,
    TARGET_QUEUE_PREPEND = 0x12,
    TARGET_QUEUE_REMOVE_FRONT = 0x14,
    TARGET_QUEUE_REPLACE_FRONT = 0x18,
    
    TARGET_QUEUE_GET_BACK = 0x21,
    TARGET_QUEUE_APPEND = 0x22,
    TARGET_QUEUE_REMOVE_BACK = 0x24,
    TARGET_QUEUE_REPLACE_BACK = 0x28,

    TARGET_QUEUE_GET_INDEX = 0x41,
    TARGET_QUEUE_REPLACE_INDEX = 0x48,

    TARGET_QUEUE_CLEAR = 0xF4,
} Target_Queue_Action_t;
class BLETargetQueueActionCharacteristic : public BLETypedCharacteristic<Target_Queue_Action_t> {
    public:
        BLETargetQueueActionCharacteristic(const char* uuid, unsigned int permissions) : BLETypedCharacteristic<Target_Queue_Action_t>(uuid, permissions) {}
};

BLEIntCharacteristic TargetQueueIndexCharacteristic(BLE_UUID_CORALS_TARGETS_QUEUE_INDEX_CHARACTERISTIC, BLEWrite);
BLETargetQueueActionCharacteristic TargetActionCharacteristic(BLE_UUID_CORALS_TARGETS_ACTION_CHARACTERISTIC, BLERead | BLEWrite);
BLEDoubleCharacteristic TargetQ0Characteristic(BLE_UUID_CORALS_TARGETS_Q0_CHARACTERISTIC, BLERead | BLEWrite);
BLEDoubleCharacteristic TargetQ1Characteristic(BLE_UUID_CORALS_TARGETS_Q1_CHARACTERISTIC, BLERead | BLEWrite);
BLEDoubleCharacteristic TargetQ2Characteristic(BLE_UUID_CORALS_TARGETS_Q2_CHARACTERISTIC, BLERead | BLEWrite);
BLEDoubleCharacteristic TargetQ3Characteristic(BLE_UUID_CORALS_TARGETS_Q3_CHARACTERISTIC, BLERead | BLEWrite);

// BLE Attitude Characteristics
BLEDoubleCharacteristic AttitudeQ0Characteristic(BLE_UUID_CORALS_ATTITUDE_Q0_CHARACTERISTIC, BLERead);
BLEDoubleCharacteristic AttitudeQ1Characteristic(BLE_UUID_CORALS_ATTITUDE_Q1_CHARACTERISTIC, BLERead);
BLEDoubleCharacteristic AttitudeQ2Characteristic(BLE_UUID_CORALS_ATTITUDE_Q2_CHARACTERISTIC, BLERead);
BLEDoubleCharacteristic AttitudeQ3Characteristic(BLE_UUID_CORALS_ATTITUDE_Q3_CHARACTERISTIC, BLERead);

// BLE Errors Characteristics - TBD

// BLE States Characteristics
BLEDoubleCharacteristic PrimaryVoltageCharacteristic(BLE_UUID_CORALS_STATES_PRIMARY_VOLTAGE_CHARACTERISTIC, BLERead);
BLEDoubleCharacteristic SecondaryVoltageCharacteristic(BLE_UUID_CORALS_STATES_SECONDARY_VOLTAGE_CHARACTERISTIC, BLERead);
BLEDoubleCharacteristic SingularityParameterCharacteristic(BLE_UUID_CORALS_STATES_SINGULARITY_PARAMETER_CHARACTERISTIC, BLERead);
BLEIntCharacteristic TargetListLengthCharacteristic(BLE_UUID_CORALS_STATES_TARGET_LIST_LENGTH_CHARACTERISTIC, BLERead);

// BLE Devices
BLEDevice DARTS;

// BLE Initialization
bool BLE_Initialized = false;

static bool DARTS_Connect() {
    if (!BLE_Initialized) {
        CORALS_DEBUG_PRINTLN("BLE not initialized.");
        return false;
    }

    if (!DARTS.connected()) {
        CORALS_DEBUG_PRINTLN("DARTS not connected.");
        return false;
    }

    return true;
}

#endif // GIGA_R1_M4

} // end namespace

void API_Init() {
    CORALS_SERIAL_PRINTLN("Initializing CORALS API...");

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
    Set_Target_List_Length(0);

#else // GIGA_R1_M4

    // BLE Initialization
    unsigned long BLE_Init_Start = millis();
    while (!BLE.begin() && millis() - BLE_Init_Start < 10000) continue;
    if (!BLE.begin()) {
        CORALS_SERIAL_PRINTLN("BLE Initialization failed.");
        return;
    }

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
    TargetsService.addCharacteristic(TargetActionCharacteristic);
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

#endif // CORE_TYPE

    CORALS_SERIAL_PRINTLN("CORALS API Initialized.");
}

void API_Loop() {
#ifdef GIGA_R1_M4

#endif // GIGA_R1_M4
}

} // end namespace CORALS