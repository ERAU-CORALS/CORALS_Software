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

namespace CORALS {
namespace Telcommunication {
namespace Telecommands {

using ::Telecommunication::Command;
using ::Telecommunication::Keyword;
using ::Telecommunication::TeleMessage;
using ::Telecommunication::Telecommunication;
using ::Telecommunication::TelecommunicationInterpreter;

SetInterpreter::SetInterpreter(const Telecommunication *telecommunicator) 
    : TelecommunicationInterpreter(telecommunicator, Command::TC_SET, SET_KEYWORDS, SET_KEYWORD_COUNT) {}

SetInterpreter::~SetInterpreter() {}

void SetInterpreter::Interpret(TeleMessage message) {
    // Parse data
    // Set value
}

} // end namespace Telecommands
} // end namespace Telcommunication
} // end namespace CORALS