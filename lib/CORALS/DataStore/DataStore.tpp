/**
 ********************************************************************************
 * @file    DataStore.tpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS DataStore Module
 * @version 1.0
 * @date    2024-03-22
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __DATASTORE_HPP__
#define __DATASTORE_HPP__

#include "DataStore_Configuration.hpp"

namespace CORALS {
namespace DataStore {

enum class MemoryMap : uint16_t {
    Start = DATASTORE_START,
    // Control Settings
    ControlSectionStart = DATASTORE_START + DATASTORE_SECTION_BUFFER,
    ControlGain11,
    ControlGain12 = ControlGain11 + sizeof(double),
    ControlGain13 = ControlGain12 + sizeof(double),
    ControlGain21 = ControlGain13 + sizeof(double),
    ControlGain22 = ControlGain21 + sizeof(double),
    ControlGain23 = ControlGain22 + sizeof(double),
    ControlGain31 = ControlGain23 + sizeof(double),
    ControlGain32 = ControlGain31 + sizeof(double),
    ControlGain33 = ControlGain32 + sizeof(double),
    ControlPeriod = ControlGain33 + sizeof(double),
    CommPeriod = ControlPeriod + sizeof(long),
    ControlSectionEnd = CommPeriod + sizeof(long),
    // Power Control
    PowerSectionStart = ControlSectionEnd + DATASTORE_SECTION_BUFFER,
    GimbalPower,
    SpinPower,
    PowerSectionEnd,
    // Status
    StatusSectionStart = PowerSectionEnd + DATASTORE_SECTION_BUFFER,
    ArgumentStatus,
    HaltStatus,
    QuatDisagreeStatus,
    QuatFormat,
    SingularityStatus,
    StatusSectionEnd,
    // Singularity
    SingularitySectionStart = StatusSectionEnd + DATASTORE_SECTION_BUFFER,
    SingularityHalting,
    SingularityThreshold,
    SingularityTrip = SingularityThreshold + sizeof(double),
    SingularitySectionEnd,
    // Data
    DataSectionStart = SingularitySectionEnd + DATASTORE_SECTION_BUFFER,
    Q0 = DataSectionStart + sizeof(double),
    Q1 = Q0 + sizeof(double),
    Q2 = Q1 + sizeof(double),
    Q3 = Q2 + sizeof(double),
    Q4 = Q0,
    GimbalAngle1 = Q3 + sizeof(double),
    GimbalAngle2 = GimbalAngle1 + sizeof(double),
    GimbalAngle3 = GimbalAngle2 + sizeof(double),
    GimbalAngle4 = GimbalAngle3 + sizeof(double),
    DataSectionEnd = GimbalAngle4 + sizeof(double),
    End = DATASTORE_END
};

uint8_t ReadByte(uint16_t address) {
    return DATASTORE.read(address);
}

void WriteByte(uint16_t address, uint8_t data) {
    DATASTORE.write(address, data);
}

template<typename T>
T Read(MemoryMap address) {
    T data;
    for (uint16_t i = 0; i < sizeof(T); i++) {
        ((uint8_t*)&data)[i] = ReadByte(address + i);
    }
    return data;
}

template<typename T>
void Write(MemoryMap address, T data) {
    for (uint16_t i = 0; i < sizeof(T); i++) {
        WriteByte(address + i, ((uint8_t*)&data)[i]);
    }
}

} // end namespace DataStore
} // end namespace CORALS

#endif // __DATASTORE_HPP__