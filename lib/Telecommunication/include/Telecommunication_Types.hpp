/**
 ********************************************************************************
 * @file    Telecommunication_Types.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Base Types for Telecommunication
 * @version 1.0
 * @date    2024-03-22
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __TELECOMMUNICATION_TYPES_HPP__
#define __TELECOMMUNICATION_TYPES_HPP__

#include <stdint.h>

namespace Telecommunication {

using Checksum = uint32_t;
using String = char*;
using CString = const char*;
using StringSize = uint32_t;

enum class Command {
    // Telecommands
    TC_SET = 0,
    TC_ECHO,
    TC_TARGET_ADD,
    TC_HALT,
    TC_SET_POWER,
    TC_SET_INERTIA,
    TC_SET_CONTROL,
    TC_SET_SINGULARITY,
    TC_SET_ERROR,
    TC_CLEAR_ERRORS,
    // Telemetry Requests
    TR_GET,
    TR_GET_TARGET,
    TR_GET_HALT,
    TR_GET_POWER,
    TR_GET_INERTIA,
    TR_GET_CONTROL,
    TR_GET_SINGULARITY,
    TR_GET_STATE,
    TR_GET_ATTITUDE,
    TR_GET_ERROR,
    TR_GET_ERRORS,
    // Telemetry Replies
    TR_REGISTER,
    TR_ECHO_REPLY,
    TR_CURRENT_TARGET,
    TR_TARGET_LIST,
    TR_HALT_STATE,
    TR_POWER_STATE,
    TR_INERTIA_MATRIX,
    TR_CONTROL_STATE,
    TR_SINGULARITY_STATE,
    TR_CORALS_STATE,
    TR_ATTITUDE,
    TR_ERROR_STATE,
    // Other Values
    COMMAND_COUNT,
    NO_COMMAND,
    RECEIVING_COMMAND_COUNT = Command::TR_REGISTER,
};

enum class Keyword {
    KW_ARGUMENT_ERROR = 0,
    KW_COMM_LR,
    KW_CONTROL_LR,
    KW_ENABLE_OVERRIDE,
    KW_GAIN11,
    KW_GAIN12,
    KW_GAIN13,
    KW_GAIN21,
    KW_GAIN22,
    KW_GAIN23,
    KW_GAIN31,
    KW_GAIN32,
    KW_GAIN33,
    KW_GM_MASTER_POWER,
    KW_HALT_STATUS,
    KW_Q0,
    KW_Q1,
    KW_Q2,
    KW_Q3,
    KW_Q4,
    KW_QUAT_DISAGREE_ERROR,
    KW_QUAT_FORMAT,
    KW_SINGULARITY_HALTING,
    KW_SINGULARITY_OVERRIDE_ERROR,
    KW_SINGULARITY_THOLD,
    KW_SINGULARITY_TRIP,
    KW_SM_MASTER_POWER,
    KW_TARGET_NUM,
    // Other Values
    KEYWORD_COUNT,
    NO_KEYWORD,
    ALL_KEYWORDS = Keyword::KEYWORD_COUNT,
};

enum class ParameterDomain {
    SET,
    RANGE,
    ANY
};

enum class ParameterType {
    INTEGER,
    DECIMAL,
    STRING,
};

union Value {
    long int integer;
    double decimal;
    String string;
};

extern "C" typedef struct KeywordParameter {
    ParameterDomain domain;
    ParameterType datatype;
    StringSize length;
    union {
        void *any;
        long int *integer;
        double *decimal;
        String *string;
    };
} KeywordParameter_t;

struct KeyValue {
    Keyword keyword;
    ParameterType type;
    Value value;
};

struct TeleMessage {
    Command command;
    KeyValue *key_value_pairs;
    uint8_t pair_count;
    uint32_t checksum;
    bool valid;
};

} // end namespace Telecommunication

#endif // __TELECOMMUNICATION_TYPES_HPP__