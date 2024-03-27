/**
 ********************************************************************************
 * @file    Telecommunication_Literals.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   String Literals for Telecommunication
 * @version 1.0
 * @date    2024-03-22
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __TELECOMMAND_LITERALS_HPP__
#define __TELECOMMAND_LITERALS_HPP__

#include <string.h>

#include "Telecommunication_Types.hpp"

namespace Telecommunication {
inline namespace Literals {

CString RECEIVER = "CORALS";
const StringSize RECEIVER_LENGTH = strlen(RECEIVER);
CString DESTINATION = "DARTS";
const StringSize DESTINATION_LENGTH = strlen(DESTINATION);
CString COMMAND_DELIMITER = " . ";
const StringSize COMMAND_DELIMITER_LENGTH = strlen(COMMAND_DELIMITER);
CString KEYVALUE_DELIMITER = ", ";
const StringSize KEYVALUE_DELIMITER_LENGTH = strlen(KEYVALUE_DELIMITER);

CString CommandLiterals[(int)Command::COMMAND_COUNT] = {
    "SET",
    "ECHO",
    "TARGET_ADD",
    "HALT",
    "SET_POWER",
    "SET_INERTIA",
    "SET_CONTROL",
    "SET_SINGULARITY",
    "SET_ERROR",
    "CLEAR_ERRORS",
    "GET",
    "GET_TARGET",
    "GET_HALT",
    "GET_POWER",
    "GET_INERTIA",
    "GET_CONTROL",
    "GET_SINGULARITY",
    "GET_STATE",
    "GET_ATTITUDE",
    "GET_ERROR",
    "GET_ERRORS",
    "REGISTER",
    "ECHO_REPLY",
    "CURRENT_TARGET",
    "TARGET_LIST",
    "HALT_STATE",
    "POWER_STATE",
    "INERTIA_MATRIX",
    "CONTROL_STATE",
    "SINGULARITY_STATE",
    "CORALS_STATE",
    "ATTITUDE",
    "ERROR_STATE"
};

CString KeywordLiterals[(int)Keyword::KEYWORD_COUNT] = {
    "ARGUMENT_ERROR",
    "COMM_LR",
    "CONTROL_LR",
    "ENABLE_OVERRIDE",
    "GAIN11",
    "GAIN12",
    "GAIN13",
    "GAIN21",
    "GAIN22",
    "GAIN23",
    "GAIN31",
    "GAIN32",
    "GAIN33",
    "GM_MASTER_POWER",
    "HALT_STATUS",
    "Q0",
    "Q1",
    "Q2",
    "Q3",
    "Q4",
    "QUAT_DISAGREE_ERROR",
    "QUAT_FORMAT",
    "SINGULARITY_HALTING",
    "SINGULARITY_OVERRIDE_ERROR",
    "SINGULARITY_THOLD",
    "SINGULARITY_TRIP",
    "SM_MASTER_POWER",
    "TARGET_NUM"
};

CString ON_LITERAL = "ON";
CString OFF_LITERAL = "OFF";
CString ON_OFF_SET[] = {ON_LITERAL, OFF_LITERAL};

CString ACTIVE_LITERAL = "ACTIVE";
CString INACTIVE_LITERAL = "INACTIVE";
CString ACTIVE_INACTIVE_SET[] = {ACTIVE_LITERAL, INACTIVE_LITERAL};

CString QUAT_FORMAT_SET[] = {KeywordLiterals[(int)Keyword::KW_Q0], KeywordLiterals[(int)Keyword::KW_Q4]};

double NORM_RANGE[] = {0.0, 1.0};

const KeywordParameter_t KeywordParameters[(int)Keyword::KEYWORD_COUNT] = {
    {ParameterDomain::SET,   ParameterType::STRING,  2, (void*)ON_OFF_SET},
    {ParameterDomain::ANY,   ParameterType::DECIMAL, 0, NULL},
    {ParameterDomain::ANY,   ParameterType::DECIMAL, 0, NULL},
    {ParameterDomain::SET,   ParameterType::STRING,  2, (void*)ON_OFF_SET},
    {ParameterDomain::ANY,   ParameterType::DECIMAL, 0, NULL},
    {ParameterDomain::ANY,   ParameterType::DECIMAL, 0, NULL},
    {ParameterDomain::ANY,   ParameterType::DECIMAL, 0, NULL},
    {ParameterDomain::ANY,   ParameterType::DECIMAL, 0, NULL},
    {ParameterDomain::ANY,   ParameterType::DECIMAL, 0, NULL},
    {ParameterDomain::ANY,   ParameterType::DECIMAL, 0, NULL},
    {ParameterDomain::ANY,   ParameterType::DECIMAL, 0, NULL},
    {ParameterDomain::ANY,   ParameterType::DECIMAL, 0, NULL},
    {ParameterDomain::ANY,   ParameterType::DECIMAL, 0, NULL},
    {ParameterDomain::SET,   ParameterType::STRING,  2, (void*)ON_OFF_SET},
    {ParameterDomain::SET,   ParameterType::STRING,  2, (void*)ACTIVE_INACTIVE_SET},
    {ParameterDomain::RANGE, ParameterType::DECIMAL, 0, (void*)NORM_RANGE},
    {ParameterDomain::RANGE, ParameterType::DECIMAL, 0, (void*)NORM_RANGE},
    {ParameterDomain::RANGE, ParameterType::DECIMAL, 0, (void*)NORM_RANGE},
    {ParameterDomain::RANGE, ParameterType::DECIMAL, 0, (void*)NORM_RANGE},
    {ParameterDomain::RANGE, ParameterType::DECIMAL, 0, (void*)NORM_RANGE},
    {ParameterDomain::SET,   ParameterType::STRING,  2, (void*)ON_OFF_SET},
    {ParameterDomain::SET,   ParameterType::STRING,  2, (void*)QUAT_FORMAT_SET},
    {ParameterDomain::SET,   ParameterType::STRING,  2, (void*)ON_OFF_SET},
    {ParameterDomain::SET,   ParameterType::STRING,  2, (void*)ON_OFF_SET},
    {ParameterDomain::RANGE, ParameterType::DECIMAL, 0, (void*)NORM_RANGE},
    {ParameterDomain::SET,   ParameterType::STRING,  2, (void*)ACTIVE_INACTIVE_SET},
    {ParameterDomain::SET,   ParameterType::STRING,  2, (void*)ON_OFF_SET},
    {ParameterDomain::ANY,   ParameterType::INTEGER, 0, NULL}
};

} // end namespace Literals
} // end namespace Telecommunication

#endif // __TELECOMMAND_LITERALS_HPP__