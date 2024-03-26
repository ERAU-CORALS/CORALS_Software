/**
 ********************************************************************************
 * @file    Set_Interpreter.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Set Interpreter
 * @version 1.0
 * @date    2024-03-22
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __SET_INTERPRETER_HPP__
#define __SET_INTERPRETER_HPP__

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

const Keyword SET_KEYWORDS[] = { Keyword::ALL_KEYWORDS };
const unsigned int SET_KEYWORD_COUNT = sizeof(SET_KEYWORDS) / sizeof(Keyword);

class SetInterpreter : private TelecommunicationInterpreter {
public:
    SetInterpreter(const Telecommunication *telecommunicator);
    ~SetInterpreter();

    void Interpret(TeleMessage message) {
        // Parse data
        // Set value
    }
};

} // end namespace Telecommands
} // end namespace Telcommunication
} // end namespace CORALS

#endif // __SET_INTERPRETER_HPP__