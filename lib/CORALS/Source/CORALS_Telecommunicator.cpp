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

#include "Internal/CORALS_BLE.inc"

#include "RxMessageBase.tpp"
#include "TxMessageBase.tpp"
#include "Telecommunicator.hpp"

namespace CORALS {

namespace {

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


} // end namespace

void initialize() {
    CORALS_DEBUG_PRINTLN("Initializing CORALS Telecommunicator...");

    // Register Message Handlers
    CORALS_Telecommunicator.Register_Handle(&CORALS_1R);
    // CORALS_Telecommunicator.Register_Handle(&CORALS_2R);
    // CORALS_Telecommunicator.Register_Handle(&CORALS_3R);
    CORALS_Telecommunicator.Register_Handle(&CORALS_4R);
    // CORALS_Telecommunicator.Register_Handle(&CORALS_5R);

    CORALS_Telecommunicator.Register_Handle(&CORALS_1T);
    CORALS_Telecommunicator.Register_Handle(&CORALS_2T);
    // CORALS_Telecommunicator.Register_Handle(&CORALS_3T);
    CORALS_Telecommunicator.Register_Handle(&CORALS_4T);
    // CORALS_Telecommunicator.Register_Handle(&CORALS_5T);

    CORALS_DEBUG_PRINTLN("CORALS Telecommunicator Initialized.");
}

void run() {
    CORALS_Telecommunicator.run();
}

} // end namespace CORALS