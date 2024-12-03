/**
 ********************************************************************************
 * @file    CORALS_Telecommunicator.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS Telecommunication Manager
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "CORALS_Telecommunicator.hpp"
#include "CORALS_Configuration.hpp"
#include "CORALS_Messages.hpp"
#include "CORALS_API.hpp"

#include <ArduinoBLE.h>
#include "Internal/CORALS_BLE.inc"

#include "RxMessageBase.tpp"
#include "TxMessageBase.tpp"
#include "Telecommunicator.hpp"

namespace CORALS {

namespace {

bool BLE_Initialized = false;

#ifdef GIGA_R1_M7

#else // GIGA_R1_M4
// BLE Devices
BLEDevice DARTS;

// BLE Services
BLEService Receive_Service(BLE_UUID_CORALS_RECEIVE_SERVICE);
BLEService Transmit_Service(BLE_UUID_CORALS_TRANSMIT_SERVICE);

::Telecommunication::Telecommunicator CORALS_Telecommunicator;

::Telecommunication::RxMessageBase<Messages::CORALS_1R> CORALS_1R (BLE_UUID_CORALS_1R_CHARACTERISTIC);
// ::Telecommunication::RxMessageBase<CORALS::Messages::CORALS_2R> CORALS_2R (BLE_UUID_CORALS_2R_CHARACTERISTIC);
// ::Telecommunication::RxMessageBase<CORALS::Messages::CORALS_3R> CORALS_3R (BLE_UUID_CORALS_3R_CHARACTERISTIC);
::Telecommunication::RxMessageBase<Messages::CORALS_4R> CORALS_4R (BLE_UUID_CORALS_4R_CHARACTERISTIC);
// ::Telecommunication::RxMessageBase<CORALS::Messages::CORALS_5R> CORALS_5R (BLE_UUID_CORALS_5R_CHARACTERISTIC);

::Telecommunication::TxMessageBase<Messages::CORALS_1T> CORALS_1T (BLE_UUID_CORALS_1T_CHARACTERISTIC, ::Telecommunication::TxCondition::ON_CHANGE);
::Telecommunication::TxMessageBase<Messages::CORALS_2T> CORALS_2T (BLE_UUID_CORALS_2T_CHARACTERISTIC, ::Telecommunication::TxCondition::ON_CHANGE_OR_INTERVAL, 200);
// ::Telecommunication::TxMessageBase<CORALS::Messages::CORALS_3T> CORALS_3T (BLE_UUID_CORALS_3T_CHARACTERISTIC, ::Telecommunication::TxCondition::ON_CHANGE);
::Telecommunication::TxMessageBase<Messages::CORALS_4T> CORALS_4T (BLE_UUID_CORALS_4T_CHARACTERISTIC, ::Telecommunication::TxCondition::ON_CHANGE);
// ::Telecommunication::TxMessageBase<CORALS::Messages::CORALS_5T> CORALS_5T (BLE_UUID_CORALS_5T_CHARACTERISTIC, ::Telecommunication::TxCondition::ON_CHANGE);

void Process_1R(Messages::CORALS_1R &CORALS_1R);
// void Process_2R(Messages::CORALS_2R &CORALS_2R);
// void Process_3R(Messages::CORALS_3R &CORALS_3R);
void Process_4R(Messages::CORALS_4R &CORALS_4R);
// void Process_5R(Messages::CORALS_5R &CORALS_5R);

// void Process_1T();
void Process_2T();
// void Process_3T();
// void Process_4T();
// void Process_5T();

Messages::CORALS_1T CORALS_1T_Value;
Messages::CORALS_2T CORALS_2T_Value;
// Messages::CORALS_3T CORALS_3T_Value;
Messages::CORALS_4T CORALS_4T_Value;
// Messages::CORALS_5T CORALS_5T_Value;
#endif // CORE TYPE

} // end namespace

void TC_Init() {
    CORALS_DEBUG_PRINTLN("Initializing CORALS Telecommunicator...");

#ifdef GIGA_R1_M7

    // DO NOTHING ON M7

#else // GIGA_R1_M4

    // BLE Device Name
    BLE.setDeviceName(BLE_DEVICE_NAME_CORALS);
    BLE.setLocalName(BLE_DEVICE_LOCAL_NAME_CORALS);

    // Receive Message Handlers
    CORALS_1R.AddService(&Receive_Service);
    // CORALS_2R.AddService(&Receive_Service);
    // CORALS_3R.AddService(&Receive_Service);
    CORALS_4R.AddService(&Receive_Service);
    // CORALS_5R.AddService(&Receive_Service);

    CORALS_Telecommunicator.Register_Handle(&CORALS_1R);
    // CORALS_Telecommunicator.Register_Handle(&CORALS_2R);
    // CORALS_Telecommunicator.Register_Handle(&CORALS_3R);
    CORALS_Telecommunicator.Register_Handle(&CORALS_4R);
    // CORALS_Telecommunicator.Register_Handle(&CORALS_5R);

    // Transmit Message Handlers
    CORALS_1T.AddService(&Transmit_Service);
    CORALS_2T.AddService(&Transmit_Service);
    // CORALS_3T.AddService(&Transmit_Service);
    CORALS_4T.AddService(&Transmit_Service);
    // CORALS_5T.AddService(&Transmit_Service);

    CORALS_Telecommunicator.Register_Handle(&CORALS_1T);
    CORALS_Telecommunicator.Register_Handle(&CORALS_2T);
    // CORALS_Telecommunicator.Register_Handle(&CORALS_3T);
    CORALS_Telecommunicator.Register_Handle(&CORALS_4T);
    // CORALS_Telecommunicator.Register_Handle(&CORALS_5T);

    BLE.setAdvertisedServiceUuid(BLE_UUID_CORALS_ADVERTISEMENT);
    BLE.advertise();

    BLE_Initialized = true;

#endif // CORE TYPE

    CORALS_DEBUG_PRINTLN("CORALS Telecommunicator Initialized.");
}

void TC_Run() {
#ifdef GIGA_R1_M7
    
    if (BLE_Initialized) {
        CORALS_OUT_PRINTLN("ERROR - BLE Initialized on M7");
    }

#else // GIGA_R1_M4

    if (!BLE_Initialized) {
        CORALS_OUT_PRINTLN("ERROR - BLE Not Initialized");
        return;
    }

    DARTS = BLE.central();
    if (!bool(DARTS) && !DARTS.connected()) {
        CORALS_OUT_PRINTLN("ERROR - BLE Not Connected");
        return;
    }

    Messages::CORALS_1R CORALS_1R_Value;
    // Messages::CORALS_2R CORALS_2R_Value;
    // Messages::CORALS_3R CORALS_3R_Value;
    Messages::CORALS_4R CORALS_4R_Value;
    // Messages::CORALS_5R CORALS_5R_Value;
    
    CORALS_Telecommunicator.run();

    if (CORALS_1R.updated()) {
        CORALS_1R.get(&CORALS_1R_Value);
        Process_1R(CORALS_1R_Value);
    }

    // if (CORALS_2R.updated()) {
    //     CORALS_2R.get(&CORALS_2R_Value);
    //     Process_2R(CORALS_2R_Value);
    // }

    // if (CORALS_3R.updated()) {
    //     CORALS_3R.get(&CORALS_3R_Value);
    //     Process_3R(CORALS_3R_Value);
    // }

    if (CORALS_4R.updated()) {
        CORALS_4R.get(&CORALS_4R_Value);
        Process_4R(CORALS_4R_Value);
    }

    // if (CORALS_5R.updated()) {
    //     CORALS_5R.get(&CORALS_5R_Value);
    //     Process_5R(CORALS_5R_Value);
    // }

    // Process_1T();
    Process_2T();
    // Process_3T();
    // Process_4T();
    // Process_5T();

    CORALS_1T.set(&CORALS_1T_Value);
    CORALS_2T.set(&CORALS_2T_Value);
    // CORALS_3T.set(&CORALS_3T_Value);
    CORALS_4T.set(&CORALS_4T_Value);
    // CORALS_5T.set(&CORALS_5T_Value);

#endif // CORE TYPE
}

namespace {

#ifdef GIGA_R1_M7

#else // GIGA_R1_M4

void Process_1R(Messages::CORALS_1R &CORALS_1R) {
    if (!CORALS_1R.W1.data.command_active) {
        CORALS_1T_Value.W1.data.command_complete = 1;
        return;
    }

    CORALS_1T_Value.W1.data.command_complete = 0;

    switch (CORALS_1R.W1.data.action) {
        case Messages::Target_Action::TARGET_GET: 
            {
                ListSize_t index = 0;

                switch (CORALS_1R.W1.data.target) {
                    case Messages::Target_Type::TARGET_BACK:
                        index = -1;
                        break;
                    case Messages::Target_Type::TARGET_FRONT:
                        index = 0;
                        break;
                    case Messages::Target_Type::TARGET_INDEX:
                        index = CORALS_1R.W1.data.index;
                        break;

                    default:
                        return;
                }

                double quaternion_value = 0.0;
                int quaternion_value_fixed = 0;

                Get_Indexed_Target_Q0(index, quaternion_value);
                quaternion_value_fixed = quaternion_value * 10000;

                CORALS_1T_Value.W2.data.reported_q0_10ths = (quaternion_value_fixed / 1000) % 10;
                CORALS_1T_Value.W2.data.reported_q0_100ths = (quaternion_value_fixed / 100) % 10;
                CORALS_1T_Value.W2.data.reported_q0_1000ths = (quaternion_value_fixed / 10) % 10;
                CORALS_1T_Value.W2.data.reported_q0_10000ths = quaternion_value_fixed % 10;
                CORALS_1T_Value.W1.data.reported_q0_negative = quaternion_value < 0;

                Get_Indexed_Target_Q1(index, quaternion_value);
                quaternion_value_fixed = quaternion_value * 10000;

                CORALS_1T_Value.W3.data.reported_q1_10ths = (quaternion_value_fixed / 1000) % 10;
                CORALS_1T_Value.W3.data.reported_q1_100ths = (quaternion_value_fixed / 100) % 10;
                CORALS_1T_Value.W3.data.reported_q1_1000ths = (quaternion_value_fixed / 10) % 10;
                CORALS_1T_Value.W3.data.reported_q1_10000ths = quaternion_value_fixed % 10;
                CORALS_1T_Value.W1.data.reported_q1_negative = quaternion_value < 0;

                Get_Indexed_Target_Q2(index, quaternion_value);
                quaternion_value_fixed = quaternion_value * 10000;

                CORALS_1T_Value.W4.data.reported_q2_10ths = (quaternion_value_fixed / 1000) % 10;
                CORALS_1T_Value.W4.data.reported_q2_100ths = (quaternion_value_fixed / 100) % 10;
                CORALS_1T_Value.W4.data.reported_q2_1000ths = (quaternion_value_fixed / 10) % 10;
                CORALS_1T_Value.W4.data.reported_q2_10000ths = quaternion_value_fixed % 10;
                CORALS_1T_Value.W1.data.reported_q2_negative = quaternion_value < 0;

                Get_Indexed_Target_Q3(index, quaternion_value);
                quaternion_value_fixed = quaternion_value * 10000;

                CORALS_1T_Value.W5.data.reported_q3_10ths = (quaternion_value_fixed / 1000) % 10;
                CORALS_1T_Value.W5.data.reported_q3_100ths = (quaternion_value_fixed / 100) % 10;
                CORALS_1T_Value.W5.data.reported_q3_1000ths = (quaternion_value_fixed / 10) % 10;
                CORALS_1T_Value.W5.data.reported_q3_10000ths = quaternion_value_fixed % 10;
                CORALS_1T_Value.W1.data.reported_q3_negative = quaternion_value < 0;
            
            } break;

        case Messages::Target_Action::TARGET_ADD:
            {
                int quaternion_value_fixed = 0;
                double quaternion_value[] = {0.0, 0.0, 0.0, 0.0};

                quaternion_value_fixed = CORALS_1R.W2.data.commanded_q0_10ths * 1000;
                quaternion_value_fixed += CORALS_1R.W2.data.commanded_q0_100ths * 100;
                quaternion_value_fixed += CORALS_1R.W2.data.commanded_q0_1000ths * 10;
                quaternion_value_fixed += CORALS_1R.W2.data.commanded_q0_10000ths;
                quaternion_value_fixed *= CORALS_1R.W1.data.commanded_q0_negative ? -1 : 1;
                
                quaternion_value[0] = quaternion_value_fixed / 10000.0;

                quaternion_value_fixed = CORALS_1R.W3.data.commanded_q1_10ths * 1000;
                quaternion_value_fixed += CORALS_1R.W3.data.commanded_q1_100ths * 100;
                quaternion_value_fixed += CORALS_1R.W3.data.commanded_q1_1000ths * 10;
                quaternion_value_fixed += CORALS_1R.W3.data.commanded_q1_10000ths;
                quaternion_value_fixed *= CORALS_1R.W1.data.commanded_q1_negative ? -1 : 1;

                quaternion_value[1] = quaternion_value_fixed / 10000.0;

                quaternion_value_fixed = CORALS_1R.W4.data.commanded_q2_10ths * 1000;
                quaternion_value_fixed += CORALS_1R.W4.data.commanded_q2_100ths * 100;
                quaternion_value_fixed += CORALS_1R.W4.data.commanded_q2_1000ths * 10;
                quaternion_value_fixed += CORALS_1R.W4.data.commanded_q2_10000ths;
                quaternion_value_fixed *= CORALS_1R.W1.data.commanded_q2_negative ? -1 : 1;

                quaternion_value[2] = quaternion_value_fixed / 10000.0;

                quaternion_value_fixed = CORALS_1R.W5.data.commanded_q3_10ths * 1000;
                quaternion_value_fixed += CORALS_1R.W5.data.commanded_q3_100ths * 100;
                quaternion_value_fixed += CORALS_1R.W5.data.commanded_q3_1000ths * 10;
                quaternion_value_fixed += CORALS_1R.W5.data.commanded_q3_10000ths;
                quaternion_value_fixed *= CORALS_1R.W1.data.commanded_q3_negative ? -1 : 1;

                quaternion_value[3] = quaternion_value_fixed / 10000.0;

                switch (CORALS_1R.W1.data.target) {
                    case Messages::Target_Type::TARGET_BACK:
                        Append_New_Target(quaternion_value[0], 
                                        quaternion_value[1],
                                        quaternion_value[2],
                                        quaternion_value[3]);
                        break;
                    case Messages::Target_Type::TARGET_FRONT:
                        Prepend_New_Target(quaternion_value[0], 
                                        quaternion_value[1],
                                        quaternion_value[2],
                                        quaternion_value[3]);
                        break;

                    default:
                        CORALS_1T_Value.W1.data.command_complete = 1;
                }

            } break;

        case Messages::Target_Action::TARGET_REMOVE:
            {
                switch (CORALS_1R.W1.data.target) {
                    case Messages::Target_Type::TARGET_BACK:
                        Remove_Last_Target();
                        break;
                    case Messages::Target_Type::TARGET_FRONT:
                        Remove_First_Target();
                        break;

                    default:
                        CORALS_1T_Value.W1.data.command_complete = 1;
                        return;
                }

            } break;

        case Messages::Target_Action::TARGET_REPLACE:
            {
                int quaternion_value_fixed = 0;
                double quaternion_value[] = {0.0, 0.0, 0.0, 0.0};

                quaternion_value_fixed = CORALS_1R.W2.data.commanded_q0_10ths * 1000;
                quaternion_value_fixed += CORALS_1R.W2.data.commanded_q0_100ths * 100;
                quaternion_value_fixed += CORALS_1R.W2.data.commanded_q0_1000ths * 10;
                quaternion_value_fixed += CORALS_1R.W2.data.commanded_q0_10000ths;
                quaternion_value_fixed *= CORALS_1R.W1.data.commanded_q0_negative ? -1 : 1;

                quaternion_value[0] = quaternion_value_fixed / 10000.0;

                quaternion_value_fixed = CORALS_1R.W3.data.commanded_q1_10ths * 1000;
                quaternion_value_fixed += CORALS_1R.W3.data.commanded_q1_100ths * 100;
                quaternion_value_fixed += CORALS_1R.W3.data.commanded_q1_1000ths * 10;
                quaternion_value_fixed += CORALS_1R.W3.data.commanded_q1_10000ths;
                quaternion_value_fixed *= CORALS_1R.W1.data.commanded_q1_negative ? -1 : 1;

                quaternion_value[1] = quaternion_value_fixed / 10000.0;

                quaternion_value_fixed = CORALS_1R.W4.data.commanded_q2_10ths * 1000;
                quaternion_value_fixed += CORALS_1R.W4.data.commanded_q2_100ths * 100;
                quaternion_value_fixed += CORALS_1R.W4.data.commanded_q2_1000ths * 10;
                quaternion_value_fixed += CORALS_1R.W4.data.commanded_q2_10000ths;
                quaternion_value_fixed *= CORALS_1R.W1.data.commanded_q2_negative ? -1 : 1;

                quaternion_value[2] = quaternion_value_fixed / 10000.0;

                quaternion_value_fixed = CORALS_1R.W5.data.commanded_q3_10ths * 1000;
                quaternion_value_fixed += CORALS_1R.W5.data.commanded_q3_100ths * 100;
                quaternion_value_fixed += CORALS_1R.W5.data.commanded_q3_1000ths * 10;
                quaternion_value_fixed += CORALS_1R.W5.data.commanded_q3_10000ths;
                quaternion_value_fixed *= CORALS_1R.W1.data.commanded_q3_negative ? -1 : 1;

                quaternion_value[3] = quaternion_value_fixed / 10000.0;

                switch (CORALS_1R.W1.data.target) {
                    case Messages::Target_Type::TARGET_BACK:
                        Replace_Indexed_Target(-1, quaternion_value[0], 
                                            quaternion_value[1],
                                            quaternion_value[2],
                                            quaternion_value[3]);
                        break;
                    case Messages::Target_Type::TARGET_FRONT:
                        Replace_Indexed_Target(0, quaternion_value[0], 
                                            quaternion_value[1],
                                            quaternion_value[2],
                                            quaternion_value[3]);
                        break;
                    case Messages::Target_Type::TARGET_INDEX:
                        Replace_Indexed_Target(CORALS_1R.W1.data.index, quaternion_value[0], 
                                            quaternion_value[1],
                                            quaternion_value[2],
                                            quaternion_value[3]);
                        break;

                    default:
                        break;
                }

            } break;

        default:    
            break;        
    }

    CORALS_1T_Value.W1.data.command_complete = 1;
}

// void Process_2R(Messages::CORALS_2R &CORALS_2R) {}

// void Process_3R(Messages::CORALS_3R &CORALS_3R) {}

void Process_4R(Messages::CORALS_4R &CORALS_4R) {
    if (!CORALS_4R.W1.data.command_active) {
        CORALS_4T_Value.W1.data.command_complete = 1;
        return;
    }

    CORALS_4T_Value.W1.data.command_complete = 0;

    int gain_value_fixed = 0;
    double gain_value = 0.0;

    gain_value_fixed = CORALS_4R.W2.data.commanded_gain11_10ths * 10;
    gain_value_fixed += CORALS_4R.W2.data.commanded_gain11_100ths;
    gain_value_fixed *= CORALS_4R.W1.data.commanded_gain11_negative ? -1 : 1;

    gain_value = gain_value_fixed / 100.0;
    if (CORALS_4R.W2.data.commanded_gain11_exp_negative) {
        for (uint8_t i = 0; i < CORALS_4R.W2.data.commanded_gain11_exp; i++) {
            gain_value /= 10.0;
        }
    } else {
        for (uint8_t i = 0; i < CORALS_4R.W2.data.commanded_gain11_exp; i++) {
            gain_value *= 10.0;
        }
    }
    Set_Gain11(gain_value);

    gain_value_fixed = CORALS_4R.W3.data.commanded_gain12_10ths * 10;
    gain_value_fixed += CORALS_4R.W3.data.commanded_gain12_100ths;
    gain_value_fixed *= CORALS_4R.W1.data.commanded_gain12_negative ? -1 : 1;

    gain_value = gain_value_fixed / 100.0;
    if (CORALS_4R.W3.data.commanded_gain12_exp_negative) {
        for (uint8_t i = 0; i < CORALS_4R.W3.data.commanded_gain12_exp; i++) {
            gain_value /= 10.0;
        }
    } else {
        for (uint8_t i = 0; i < CORALS_4R.W3.data.commanded_gain12_exp; i++) {
            gain_value *= 10.0;
        }
    }
    Set_Gain12(gain_value);

    gain_value_fixed = CORALS_4R.W4.data.commanded_gain13_10ths * 10;
    gain_value_fixed += CORALS_4R.W4.data.commanded_gain13_100ths;
    gain_value_fixed *= CORALS_4R.W1.data.commanded_gain13_negative ? -1 : 1;

    gain_value = gain_value_fixed / 100.0;
    if (CORALS_4R.W4.data.commanded_gain13_exp_negative) {
        for (uint8_t i = 0; i < CORALS_4R.W4.data.commanded_gain13_exp; i++) {
            gain_value /= 10.0;
        }
    } else {
        for (uint8_t i = 0; i < CORALS_4R.W4.data.commanded_gain13_exp; i++) {
            gain_value *= 10.0;
        }
    }
    Set_Gain13(gain_value);

    gain_value_fixed = CORALS_4R.W5.data.commanded_gain21_10ths * 10;
    gain_value_fixed += CORALS_4R.W5.data.commanded_gain21_100ths;
    gain_value_fixed *= CORALS_4R.W1.data.commanded_gain21_negative ? -1 : 1;

    gain_value = gain_value_fixed / 100.0;
    if (CORALS_4R.W5.data.commanded_gain21_exp_negative) {
        for (uint8_t i = 0; i < CORALS_4R.W5.data.commanded_gain21_exp; i++) {
            gain_value /= 10.0;
        }
    } else {
        for (uint8_t i = 0; i < CORALS_4R.W5.data.commanded_gain21_exp; i++) {
            gain_value *= 10.0;
        }
    }
    Set_Gain21(gain_value);

    gain_value_fixed = CORALS_4R.W6.data.commanded_gain22_10ths * 10;
    gain_value_fixed += CORALS_4R.W6.data.commanded_gain22_100ths;
    gain_value_fixed *= CORALS_4R.W1.data.commanded_gain22_negative ? -1 : 1;

    gain_value = gain_value_fixed / 100.0;
    if (CORALS_4R.W6.data.commanded_gain22_exp_negative) {
        for (uint8_t i = 0; i < CORALS_4R.W6.data.commanded_gain22_exp; i++) {
            gain_value /= 10.0;
        }
    } else {
        for (uint8_t i = 0; i < CORALS_4R.W6.data.commanded_gain22_exp; i++) {
            gain_value *= 10.0;
        }
    }
    Set_Gain22(gain_value);

    gain_value_fixed = CORALS_4R.W7.data.commanded_gain23_10ths * 10;
    gain_value_fixed += CORALS_4R.W7.data.commanded_gain23_100ths;
    gain_value_fixed *= CORALS_4R.W1.data.commanded_gain23_negative ? -1 : 1;

    gain_value = gain_value_fixed / 100.0;
    if (CORALS_4R.W7.data.commanded_gain23_exp_negative) {
        for (uint8_t i = 0; i < CORALS_4R.W7.data.commanded_gain23_exp; i++) {
            gain_value /= 10.0;
        }
    } else {
        for (uint8_t i = 0; i < CORALS_4R.W7.data.commanded_gain23_exp; i++) {
            gain_value *= 10.0;
        }
    }
    Set_Gain23(gain_value);

    gain_value_fixed = CORALS_4R.W8.data.commanded_gain31_10ths * 10;
    gain_value_fixed += CORALS_4R.W8.data.commanded_gain31_100ths;
    gain_value_fixed *= CORALS_4R.W1.data.commanded_gain31_negative ? -1 : 1;

    gain_value = gain_value_fixed / 100.0;
    if (CORALS_4R.W8.data.commanded_gain31_exp_negative) {
        for (uint8_t i = 0; i < CORALS_4R.W8.data.commanded_gain31_exp; i++) {
            gain_value /= 10.0;
        }
    } else {
        for (uint8_t i = 0; i < CORALS_4R.W8.data.commanded_gain31_exp; i++) {
            gain_value *= 10.0;
        }
    }
    Set_Gain31(gain_value);

    gain_value_fixed = CORALS_4R.W9.data.commanded_gain32_10ths * 10;
    gain_value_fixed += CORALS_4R.W9.data.commanded_gain32_100ths;
    gain_value_fixed *= CORALS_4R.W1.data.commanded_gain32_negative ? -1 : 1;

    gain_value = gain_value_fixed / 100.0;
    if (CORALS_4R.W9.data.commanded_gain32_exp_negative) {
        for (uint8_t i = 0; i < CORALS_4R.W9.data.commanded_gain32_exp; i++) {
            gain_value /= 10.0;
        }
    } else {
        for (uint8_t i = 0; i < CORALS_4R.W9.data.commanded_gain32_exp; i++) {
            gain_value *= 10.0;
        }
    }
    Set_Gain32(gain_value);

    gain_value_fixed = CORALS_4R.W10.data.commanded_gain33_10ths * 10;
    gain_value_fixed += CORALS_4R.W10.data.commanded_gain33_100ths;
    gain_value_fixed *= CORALS_4R.W1.data.commanded_gain33_negative ? -1 : 1;

    gain_value = gain_value_fixed / 100.0;
    if (CORALS_4R.W10.data.commanded_gain33_exp_negative) {
        for (uint8_t i = 0; i < CORALS_4R.W10.data.commanded_gain33_exp; i++) {
            gain_value /= 10.0;
        }
    } else {
        for (uint8_t i = 0; i < CORALS_4R.W10.data.commanded_gain33_exp; i++) {
            gain_value *= 10.0;
        }
    }
    Set_Gain33(gain_value);

    CORALS_4T_Value.W2.raw = CORALS_4R.W2.raw;
    CORALS_4T_Value.W3.raw = CORALS_4R.W3.raw;
    CORALS_4T_Value.W4.raw = CORALS_4R.W4.raw;
    CORALS_4T_Value.W5.raw = CORALS_4R.W5.raw;
    CORALS_4T_Value.W6.raw = CORALS_4R.W6.raw;
    CORALS_4T_Value.W7.raw = CORALS_4R.W7.raw;
    CORALS_4T_Value.W8.raw = CORALS_4R.W8.raw;
    CORALS_4T_Value.W9.raw = CORALS_4R.W9.raw;
    CORALS_4T_Value.W10.raw = CORALS_4R.W10.raw;

    CORALS_4T_Value.W1.data.reported_gain11_negative = CORALS_4R.W1.data.commanded_gain11_negative;
    CORALS_4T_Value.W1.data.reported_gain12_negative = CORALS_4R.W1.data.commanded_gain12_negative;
    CORALS_4T_Value.W1.data.reported_gain13_negative = CORALS_4R.W1.data.commanded_gain13_negative;
    CORALS_4T_Value.W1.data.reported_gain21_negative = CORALS_4R.W1.data.commanded_gain21_negative;
    CORALS_4T_Value.W1.data.reported_gain22_negative = CORALS_4R.W1.data.commanded_gain22_negative;
    CORALS_4T_Value.W1.data.reported_gain23_negative = CORALS_4R.W1.data.commanded_gain23_negative;
    CORALS_4T_Value.W1.data.reported_gain31_negative = CORALS_4R.W1.data.commanded_gain31_negative;
    CORALS_4T_Value.W1.data.reported_gain32_negative = CORALS_4R.W1.data.commanded_gain32_negative;
    CORALS_4T_Value.W1.data.reported_gain33_negative = CORALS_4R.W1.data.commanded_gain33_negative;

    CORALS_4T_Value.W1.data.command_complete = 1;
}

// void Process_5R(Messages::CORALS_5R &CORALS_5R) {}

// void Process_1T() {}

void Process_2T() {
    double attitude_value = 0.0;
    int attitude_value_fixed = 0;

    Get_Attitude_Q0(attitude_value);
    attitude_value_fixed = attitude_value * 10000;

    CORALS_2T_Value.W2.data.attitude_q0_10ths = (attitude_value_fixed / 1000) % 10;
    CORALS_2T_Value.W2.data.attitude_q0_100ths = (attitude_value_fixed / 100) % 10;
    CORALS_2T_Value.W2.data.attitude_q0_1000ths = (attitude_value_fixed / 10) % 10;
    CORALS_2T_Value.W2.data.attitude_q0_10000ths = attitude_value_fixed % 10;
    CORALS_2T_Value.W1.data.attitude_q0_negative = attitude_value < 0;

    Get_Attitude_Q1(attitude_value);
    attitude_value_fixed = attitude_value * 10000;

    CORALS_2T_Value.W3.data.attitude_q1_10ths = (attitude_value_fixed / 1000) % 10;
    CORALS_2T_Value.W3.data.attitude_q1_100ths = (attitude_value_fixed / 100) % 10;
    CORALS_2T_Value.W3.data.attitude_q1_1000ths = (attitude_value_fixed / 10) % 10;
    CORALS_2T_Value.W3.data.attitude_q1_10000ths = attitude_value_fixed % 10;
    CORALS_2T_Value.W1.data.attitude_q1_negative = attitude_value < 0;

    Get_Attitude_Q2(attitude_value);
    attitude_value_fixed = attitude_value * 10000;

    CORALS_2T_Value.W4.data.attitude_q2_10ths = (attitude_value_fixed / 1000) % 10;
    CORALS_2T_Value.W4.data.attitude_q2_100ths = (attitude_value_fixed / 100) % 10;
    CORALS_2T_Value.W4.data.attitude_q2_1000ths = (attitude_value_fixed / 10) % 10;
    CORALS_2T_Value.W4.data.attitude_q2_10000ths = attitude_value_fixed % 10;
    CORALS_2T_Value.W1.data.attitude_q2_negative = attitude_value < 0;

    Get_Attitude_Q3(attitude_value);
    attitude_value_fixed = attitude_value * 10000;

    CORALS_2T_Value.W5.data.attitude_q3_10ths = (attitude_value_fixed / 1000) % 10;
    CORALS_2T_Value.W5.data.attitude_q3_100ths = (attitude_value_fixed / 100) % 10;
    CORALS_2T_Value.W5.data.attitude_q3_1000ths = (attitude_value_fixed / 10) % 10;
    CORALS_2T_Value.W5.data.attitude_q3_10000ths = attitude_value_fixed % 10;
    CORALS_2T_Value.W1.data.attitude_q3_negative = attitude_value < 0;
}

// void Process_3T() {}

// void Process_4T() {}

// void Process_5T() {}

#endif // CORE TYPE

} // end namespace

} // end namespace CORALS