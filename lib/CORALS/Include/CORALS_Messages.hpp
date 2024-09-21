/**
 ********************************************************************************
 * @file    CORALS_Message.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS Telecommunication Messages
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __CORALS_MESSAGES_HPP__
#define __CORALS_MESSAGES_HPP__

#include <stdbool.h>
#include <stdint.h>

namespace CORALS {
namespace Messages {

typedef uint16_t word_t;
typedef word_t field_t;

enum Target_Type {
    TARGET_BACK = 0b01,
    TARGET_FRONT = 0b10,
    TARGET_INDEX = 0b11,
};

enum Target_Action {
    TARGET_GET = 0b00,
    TARGET_ADD = 0b01,
    TARGET_REMOVE = 0b10,
    TARGET_REPLACE = 0b11,
};

struct CORALS_1R {
    union {
        struct {
            field_t command_active : 1;
            field_t reserved1 : 1;
            field_t commanded_q0_negative : 1;
            field_t commanded_q1_negative : 1;
            field_t commanded_q2_negative : 1;
            field_t commanded_q3_negative : 1;
            Target_Type target : 2;
            Target_Action action : 2;
            field_t reserved2 : 1;
            field_t index : 5;

        } packed data;
        word_t raw;
    } W1;

    union {
        struct {
            field_t commanded_q0_10ths : 4;
            field_t commanded_q0_100ths : 4;
            field_t commanded_q0_1000ths : 4;
            field_t commanded_q0_10000ths : 4;
        } packed data;
        word_t raw;
    } W2;

    union {
        struct {
            field_t commanded_q1_10ths : 4;
            field_t commanded_q1_100ths : 4;
            field_t commanded_q1_1000ths : 4;
            field_t commanded_q1_10000ths : 4;
        } packed data;
        word_t raw;
    } W3;

    union {
        struct {
            field_t commanded_q2_10ths : 4;
            field_t commanded_q2_100ths : 4;
            field_t commanded_q2_1000ths : 4;
            field_t commanded_q2_10000ths : 4;
        } packed data;
        word_t raw;
    } W4;

    union {
        struct {
            field_t commanded_q3_10ths : 4;
            field_t commanded_q3_100ths : 4;
            field_t commanded_q3_1000ths : 4;
            field_t commanded_q3_10000ths : 4;
        } packed data;
        word_t raw;
    } W5;
} packed;

struct CORALS_1T {
    union {
        struct {
            field_t command_complete : 1;
            field_t reserved1 : 1;
            field_t reported_q0_negative : 1;
            field_t reported_q1_negative : 1;
            field_t reported_q2_negative : 1;
            field_t reported_q3_negative : 1;
            field_t reserved2 : 10;
        } packed data;
        word_t raw;
    } W1;

    union {
        struct {
            field_t reported_q0_10ths : 4;
            field_t reported_q0_100ths : 4;
            field_t reported_q0_1000ths : 4;
            field_t reported_q0_10000ths : 4;
        } packed data;
        word_t raw;
    } W2;

    union {
        struct {
            field_t reported_q1_10ths : 4;
            field_t reported_q1_100ths : 4;
            field_t reported_q1_1000ths : 4;
            field_t reported_q1_10000ths : 4;
        } packed data;
        word_t raw;
    } W3;

    union {
        struct {
            field_t reported_q2_10ths : 4;
            field_t reported_q2_100ths : 4;
            field_t reported_q2_1000ths : 4;
            field_t reported_q2_10000ths : 4;
        } packed data;
        word_t raw;
    } W4;

    union {
        struct {
            field_t reported_q3_10ths : 4;
            field_t reported_q3_100ths : 4;
            field_t reported_q3_1000ths : 4;
            field_t reported_q3_10000ths : 4;
        } packed data;
        word_t raw;
    } W5;
} packed;

struct CORALS_2R {} packed;

struct CORALS_2T {
    union {
        struct {
            field_t reserved1 : 4;
            field_t attitude_q0_negative : 1;
            field_t attitude_q1_negative : 1;
            field_t attitude_q2_negative : 1;
            field_t attitude_q3_negative : 1;
            field_t reserved2 : 8;
        } packed data;
        word_t raw;
    } W1;

    union {
        struct {
            field_t attitude_q0_10ths : 4;
            field_t attitude_q0_100ths : 4;
            field_t attitude_q0_1000ths : 4;
            field_t attitude_q0_10000ths : 4;
        } packed data;
        word_t raw;
    } W2;

    union {
        struct {
            field_t attitude_q1_10ths : 4;
            field_t attitude_q1_100ths : 4;
            field_t attitude_q1_1000ths : 4;
            field_t attitude_q1_10000ths : 4;
        } packed data;
        word_t raw;
    } W3;

    union {
        struct {
            field_t attitude_q2_10ths : 4;
            field_t attitude_q2_100ths : 4;
            field_t attitude_q2_1000ths : 4;
            field_t attitude_q2_10000ths : 4;
        } packed data;
        word_t raw;
    } W4;

    union {
        struct {
            field_t attitude_q3_10ths : 4;
            field_t attitude_q3_100ths : 4;
            field_t attitude_q3_1000ths : 4;
            field_t attitude_q3_10000ths : 4;
        } packed data;
        word_t raw;
    } W5;
} packed;

struct CORALS_3R {} packed;

struct CORALS_3T {} packed;

struct CORALS_4R {
    union {
        struct {
            field_t command_active : 1;
            field_t reserved1 : 6;
            field_t commanded_gain11_negative : 1;
            field_t commanded_gain12_negative : 1;
            field_t commanded_gain13_negative : 1;
            field_t commanded_gain21_negative : 1;
            field_t commanded_gain22_negative : 1;
            field_t commanded_gain23_negative : 1;
            field_t commanded_gain31_negative : 1;
            field_t commanded_gain32_negative : 1;
            field_t commanded_gain33_negative : 1;
        } packed data;
        word_t raw;
    } W1;

    union {
        struct {
            field_t commanded_gain11_10ths : 4;
            field_t commanded_gain11_100ths : 4;
            field_t commanded_gain11_exp_negative : 1;
            field_t commanded_gain11_exp : 7;
        } packed data;
        word_t raw;
    } W2;

    union {
        struct {
            field_t commanded_gain12_10ths : 4;
            field_t commanded_gain12_100ths : 4;
            field_t commanded_gain12_exp_negative : 1;
            field_t commanded_gain12_exp : 7;
        } packed data;
        word_t raw;
    } W3;

    union {
        struct {
            field_t commanded_gain13_10ths : 4;
            field_t commanded_gain13_100ths : 4;
            field_t commanded_gain13_exp_negative : 1;
            field_t commanded_gain13_exp : 7;
        } packed data;
        word_t raw;
    } W4;

    union {
        struct {
            field_t commanded_gain21_10ths : 4;
            field_t commanded_gain21_100ths : 4;
            field_t commanded_gain21_exp_negative : 1;
            field_t commanded_gain21_exp : 7;
        } packed data;
        word_t raw;
    } W5;

    union {
        struct {
            field_t commanded_gain22_10ths : 4;
            field_t commanded_gain22_100ths : 4;
            field_t commanded_gain22_exp_negative : 1;
            field_t commanded_gain22_exp : 7;
        } packed data;
        word_t raw;
    } W6;

    union {
        struct {
            field_t commanded_gain23_10ths : 4;
            field_t commanded_gain23_100ths : 4;
            field_t commanded_gain23_exp_negative : 1;
            field_t commanded_gain23_exp : 7;
        } packed data;
        word_t raw;
    } W7;

    union {
        struct {
            field_t commanded_gain31_10ths : 4;
            field_t commanded_gain31_100ths : 4;
            field_t commanded_gain31_exp_negative : 1;
            field_t commanded_gain31_exp : 7;
        } packed data;
        word_t raw;
    } W8;

    union {
        struct {
            field_t commanded_gain32_10ths : 4;
            field_t commanded_gain32_100ths : 4;
            field_t commanded_gain32_exp_negative : 1;
            field_t commanded_gain32_exp : 7;
        } packed data;
        word_t raw;
    } W9;

    union {
        struct {
            field_t commanded_gain33_10ths : 4;
            field_t commanded_gain33_100ths : 4;
            field_t commanded_gain33_exp_negative : 1;
            field_t commanded_gain33_exp : 7;
        } packed data;
        word_t raw;
    } W10;
} packed;

struct CORALS_4T {
    union {
        struct {
            field_t command_complete : 1;
            field_t reserved1 : 6;
            field_t reported_gain11_negative : 1;
            field_t reported_gain12_negative : 1;
            field_t reported_gain13_negative : 1;
            field_t reported_gain21_negative : 1;
            field_t reported_gain22_negative : 1;
            field_t reported_gain23_negative : 1;
            field_t reported_gain31_negative : 1;
            field_t reported_gain32_negative : 1;
            field_t reported_gain33_negative : 1;
        } packed data;
        word_t raw;
    } W1;

    union {
        struct {
            field_t reported_gain11_10ths : 4;
            field_t reported_gain11_100ths : 4;
            field_t reported_gain11_exp_negative : 1;
            field_t reported_gain11_exp : 7;
        } packed data;
        word_t raw;
    } W2;

    union {
        struct {
            field_t reported_gain12_10ths : 4;
            field_t reported_gain12_100ths : 4;
            field_t reported_gain12_exp_negative : 1;
            field_t reported_gain12_exp : 7;
        } packed data;
        word_t raw;
    } W3;

    union {
        struct {
            field_t reported_gain13_10ths : 4;
            field_t reported_gain13_100ths : 4;
            field_t reported_gain13_exp_negative : 1;
            field_t reported_gain13_exp : 7;
        } packed data;
        word_t raw;
    } W4;

    union {
        struct {
            field_t reported_gain21_10ths : 4;
            field_t reported_gain21_100ths : 4;
            field_t reported_gain21_exp_negative : 1;
            field_t reported_gain21_exp : 7;
        } packed data;
        word_t raw;
    } W5;

    union {
        struct {
            field_t reported_gain22_10ths : 4;
            field_t reported_gain22_100ths : 4;
            field_t reported_gain22_exp_negative : 1;
            field_t reported_gain22_exp : 7;
        } packed data;
        word_t raw;
    } W6;

    union {
        struct {
            field_t reported_gain23_10ths : 4;
            field_t reported_gain23_100ths : 4;
            field_t reported_gain23_exp_negative : 1;
            field_t reported_gain23_exp : 7;
        } packed data;
        word_t raw;
    } W7;

    union {
        struct {
            field_t reported_gain31_10ths : 4;
            field_t reported_gain31_100ths : 4;
            field_t reported_gain31_exp_negative : 1;
            field_t reported_gain31_exp : 7;
        } packed data;
        word_t raw;
    } W8;

    union {
        struct {
            field_t reported_gain32_10ths : 4;
            field_t reported_gain32_100ths : 4;
            field_t reported_gain32_exp_negative : 1;
            field_t reported_gain32_exp : 7;
        } packed data;
        word_t raw;
    } W9;

    union {
        struct {
            field_t reported_gain33_10ths : 4;
            field_t reported_gain33_100ths : 4;
            field_t reported_gain33_exp_negative : 1;
            field_t reported_gain33_exp : 7;
        } packed data;
        word_t raw;
    } W10;
} packed;

struct CORALS_5R {} packed;

struct CORALS_5T {} packed;

} // end namespace Messages
} // end namespace CORALS

#endif // __CORALS_MESSAGES_HPP__