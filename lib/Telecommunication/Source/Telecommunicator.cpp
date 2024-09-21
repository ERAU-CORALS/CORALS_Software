/**
 ********************************************************************************
 * @file    Telecommunicator.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Telecommunication Manager for CORALS
 * @version 1.0
 * @date    2024-09-11
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "Telecommunicator.hpp"

#include "TC_Configuration.hpp"

namespace Telecommunication {

using DataStructures::List::ListSize_t;

Telecommunicator::Telecommunicator() {
    TC_DEBUG_PRINTLN("Telecommunicator Initialized");
}

Telecommunicator::~Telecommunicator() {
    TC_DEBUG_PRINTLN("Telecommunicator Deinitialized");
}

void Telecommunicator::Register_Handle(MessageHandler *const handle) {
    mHandles.push_back(handle);
}

void Telecommunicator::run() {
    for (ListSize_t i = 0; i < mHandles.size(); i++) {
        TC_DEBUG_PRINT("Processing Rx Message: ");
        TC_DEBUG_PRINTLN(i);

        mHandles[i]->run();
    }
}

} // namespace Telecommunication