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

#endif // CORE TYPE
}

} // end namespace CORALS