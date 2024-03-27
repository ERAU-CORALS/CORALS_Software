/**
 ********************************************************************************
 * @file    Set_Interpreter.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Set Interpreter
 * @version 1.0
 * @date    2024-03-22
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "Set_Interpreter.hpp"

#include <Telecommunication.hpp>
#include <Telecommunication_Interpreter.hpp>
#include <Telecommunication_Types.hpp>

#include "DataStore.tpp"

namespace CORALS {
namespace Telcommunication {
namespace Telecommands {

using ::Telecommunication::Command;
using ::Telecommunication::Keyword;
using ::Telecommunication::KeyValue;
using ::Telecommunication::TeleMessage;
using ::Telecommunication::Telecommunication;
using ::Telecommunication::TelecommunicationInterpreter;
using namespace ::Telecommunication::Literals;

using DataStore::MemoryMap;

SetInterpreter::SetInterpreter(const Telecommunication *telecommunicator) 
    : TelecommunicationInterpreter(telecommunicator, Command::TC_SET, SET_KEYWORDS, SET_KEYWORD_COUNT) {}

SetInterpreter::~SetInterpreter() {}

void SetInterpreter::Interpret(TeleMessage message) {
    for (int i = 0; i < message.pair_count; i++) {
        KeyValue &pair = message.key_value_pairs[i];
        switch (pair.keyword) {
            case Keyword::KW_ARGUMENT_ERROR:
                DataStore::Write<uint8_t>(MemoryMap::ArgumentStatus, pair.value.string == ON_LITERAL ? 1 : 0);
                break;
            case Keyword::KW_COMM_LR:
                DataStore::Write<double>(MemoryMap::CommPeriod, pair.value.decimal);
                break;
            case Keyword::KW_CONTROL_LR:
                DataStore::Write<double>(MemoryMap::ControlPeriod, pair.value.decimal);
                break;
            case Keyword::KW_ENABLE_OVERRIDE:
                DataStore::Write<uint8_t>(MemoryMap::HaltStatus, pair.value.string == ON_LITERAL ? 1 : 0);
                break;
            case Keyword::KW_GAIN11:
                DataStore::Write<double>(MemoryMap::ControlGain11, pair.value.decimal);
                break;
            case Keyword::KW_GAIN12:
                DataStore::Write<double>(MemoryMap::ControlGain12, pair.value.decimal);
                break;
            case Keyword::KW_GAIN13:
                DataStore::Write<double>(MemoryMap::ControlGain13, pair.value.decimal);
                break;
            case Keyword::KW_GAIN21:
                DataStore::Write<double>(MemoryMap::ControlGain21, pair.value.decimal);
                break;
            case Keyword::KW_GAIN22:
                DataStore::Write<double>(MemoryMap::ControlGain22, pair.value.decimal);
                break;
            case Keyword::KW_GAIN23:
                DataStore::Write<double>(MemoryMap::ControlGain23, pair.value.decimal);
                break;
            case Keyword::KW_GAIN31:
                DataStore::Write<double>(MemoryMap::ControlGain31, pair.value.decimal);
                break;
            case Keyword::KW_GAIN32:
                DataStore::Write<double>(MemoryMap::ControlGain32, pair.value.decimal);
                break;
            case Keyword::KW_GAIN33:
                DataStore::Write<double>(MemoryMap::ControlGain33, pair.value.decimal);
                break;
            case Keyword::KW_GM_MASTER_POWER:
                DataStore::Write<uint8_t>(MemoryMap::GimbalPower, pair.value.string == ON_LITERAL ? 1 : 0);
                break;
            case Keyword::KW_HALT_STATUS:
                DataStore::Write<uint8_t>(MemoryMap::HaltStatus, pair.value.string == ACTIVE_LITERAL ? 1 : 0);
                break;
            case Keyword::KW_Q0:
                DataStore::Write<double>(MemoryMap::Roll, pair.value.decimal);
                break;
            case Keyword::KW_Q1:
                DataStore::Write<double>(MemoryMap::Pitch, pair.value.decimal);
                break;
            case Keyword::KW_Q2:
                
        }
    }
}

} // end namespace Telecommands
} // end namespace Telcommunication
} // end namespace CORALS