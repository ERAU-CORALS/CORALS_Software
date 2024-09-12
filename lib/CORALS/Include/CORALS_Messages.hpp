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

struct CORALS_1R {
    union {
        struct {
            bool command_active : 1;
            uint8_t reserved1 : 3;
            bool commanded_q0_negative : 1;
            bool commanded_q1_negative : 1;
            bool commanded_q2_negative : 1;
            bool commanded_q3_negative : 1;
            uint8_t reserved2 : 8;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W1;

    union {
        struct {
            uint8_t commanded_q0_10ths : 4;
            uint8_t commanded_q0_100ths : 4;
            uint8_t commanded_q0_1000ths : 4;
            uint8_t commanded_q0_10000ths : 4;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W2;

    union {
        struct {
            uint8_t commanded_q1_10ths : 4;
            uint8_t commanded_q1_100ths : 4;
            uint8_t commanded_q1_1000ths : 4;
            uint8_t commanded_q1_10000ths : 4;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W3;

    union {
        struct {
            uint8_t commanded_q2_10ths : 4;
            uint8_t commanded_q2_100ths : 4;
            uint8_t commanded_q2_1000ths : 4;
            uint8_t commanded_q2_10000ths : 4;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W4;

    union {
        struct {
            uint8_t commanded_q3_10ths : 4;
            uint8_t commanded_q3_100ths : 4;
            uint8_t commanded_q3_1000ths : 4;
            uint8_t commanded_q3_10000ths : 4;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W5;
} __attribute__((__packed__));

struct CORALS_1T {
    union {
        struct {
            bool command_complete : 1;
            uint8_t reserved1 : 15;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W1;
} __attribute__((__packed__));

struct CORALS_2R {} __attribute__((__packed__));

struct CORALS_2T {
    union {
        struct {
            uint8_t reserved1 : 4;
            bool attitude_q0_negative : 1;
            bool attitude_q1_negative : 1;
            bool attitude_q2_negative : 1;
            bool attitude_q3_negative : 1;
            uint8_t reserved2 : 8;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W1;

    union {
        struct {
            uint8_t attitude_q0_10ths : 4;
            uint8_t attitude_q0_100ths : 4;
            uint8_t attitude_q0_1000ths : 4;
            uint8_t attitude_q0_10000ths : 4;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W2;

    union {
        struct {
            uint8_t attitude_q1_10ths : 4;
            uint8_t attitude_q1_100ths : 4;
            uint8_t attitude_q1_1000ths : 4;
            uint8_t attitude_q1_10000ths : 4;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W3;

    union {
        struct {
            uint8_t attitude_q2_10ths : 4;
            uint8_t attitude_q2_100ths : 4;
            uint8_t attitude_q2_1000ths : 4;
            uint8_t attitude_q2_10000ths : 4;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W4;

    union {
        struct {
            uint8_t attitude_q3_10ths : 4;
            uint8_t attitude_q3_100ths : 4;
            uint8_t attitude_q3_1000ths : 4;
            uint8_t attitude_q3_10000ths : 4;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W5;
} __attribute__((__packed__));

struct CORALS_3R {} __attribute__((__packed__));

struct CORALS_3T {} __attribute__((__packed__));

struct CORALS_4R {
    union {
        struct {
            bool command_active : 1;
            uint8_t reserved1 : 6;
            bool commanded_gain11_negative : 1;
            bool commanded_gain12_negative : 1;
            bool commanded_gain13_negative : 1;
            bool commanded_gain21_negative : 1;
            bool commanded_gain22_negative : 1;
            bool commanded_gain23_negative : 1;
            bool commanded_gain31_negative : 1;
            bool commanded_gain32_negative : 1;
            bool commanded_gain33_negative : 1;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W1;

    union {
        struct {
            uint8_t commanded_gain11_10ths : 4;
            uint8_t commanded_gain11_100ths : 4;
            bool commanded_gain11_exp_negative : 1;
            uint8_t commanded_gain11_exp : 7;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W2;

    union {
        struct {
            uint8_t commanded_gain12_10ths : 4;
            uint8_t commanded_gain12_100ths : 4;
            bool commanded_gain12_exp_negative : 1;
            uint8_t commanded_gain12_exp : 7;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W3;

    union {
        struct {
            uint8_t commanded_gain13_10ths : 4;
            uint8_t commanded_gain13_100ths : 4;
            bool commanded_gain13_exp_negative : 1;
            uint8_t commanded_gain13_exp : 7;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W4;

    union {
        struct {
            uint8_t commanded_gain21_10ths : 4;
            uint8_t commanded_gain21_100ths : 4;
            bool commanded_gain21_exp_negative : 1;
            uint8_t commanded_gain21_exp : 7;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W5;

    union {
        struct {
            uint8_t commanded_gain22_10ths : 4;
            uint8_t commanded_gain22_100ths : 4;
            bool commanded_gain22_exp_negative : 1;
            uint8_t commanded_gain22_exp : 7;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W6;

    union {
        struct {
            uint8_t commanded_gain23_10ths : 4;
            uint8_t commanded_gain23_100ths : 4;
            bool commanded_gain23_exp_negative : 1;
            uint8_t commanded_gain23_exp : 7;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W7;

    union {
        struct {
            uint8_t commanded_gain31_10ths : 4;
            uint8_t commanded_gain31_100ths : 4;
            bool commanded_gain31_exp_negative : 1;
            uint8_t commanded_gain31_exp : 7;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W8;

    union {
        struct {
            uint8_t commanded_gain32_10ths : 4;
            uint8_t commanded_gain32_100ths : 4;
            bool commanded_gain32_exp_negative : 1;
            uint8_t commanded_gain32_exp : 7;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W9;

    union {
        struct {
            uint8_t commanded_gain33_10ths : 4;
            uint8_t commanded_gain33_100ths : 4;
            bool commanded_gain33_exp_negative : 1;
            uint8_t commanded_gain33_exp : 7;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W10;
} __attribute__((__packed__));

struct CORALS_4T {
    union {
        struct {
            bool command_active : 1;
            uint8_t reserved1 : 6;
            bool commanded_gain11_negative : 1;
            bool commanded_gain12_negative : 1;
            bool commanded_gain13_negative : 1;
            bool commanded_gain21_negative : 1;
            bool commanded_gain22_negative : 1;
            bool commanded_gain23_negative : 1;
            bool commanded_gain31_negative : 1;
            bool commanded_gain32_negative : 1;
            bool commanded_gain33_negative : 1;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W1;

    union {
        struct {
            uint8_t commanded_gain11_10ths : 4;
            uint8_t commanded_gain11_100ths : 4;
            bool commanded_gain11_exp_negative : 1;
            uint8_t commanded_gain11_exp : 7;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W2;

    union {
        struct {
            uint8_t commanded_gain12_10ths : 4;
            uint8_t commanded_gain12_100ths : 4;
            bool commanded_gain12_exp_negative : 1;
            uint8_t commanded_gain12_exp : 7;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W3;

    union {
        struct {
            uint8_t commanded_gain13_10ths : 4;
            uint8_t commanded_gain13_100ths : 4;
            bool commanded_gain13_exp_negative : 1;
            uint8_t commanded_gain13_exp : 7;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W4;

    union {
        struct {
            uint8_t commanded_gain21_10ths : 4;
            uint8_t commanded_gain21_100ths : 4;
            bool commanded_gain21_exp_negative : 1;
            uint8_t commanded_gain21_exp : 7;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W5;

    union {
        struct {
            uint8_t commanded_gain22_10ths : 4;
            uint8_t commanded_gain22_100ths : 4;
            bool commanded_gain22_exp_negative : 1;
            uint8_t commanded_gain22_exp : 7;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W6;

    union {
        struct {
            uint8_t commanded_gain23_10ths : 4;
            uint8_t commanded_gain23_100ths : 4;
            bool commanded_gain23_exp_negative : 1;
            uint8_t commanded_gain23_exp : 7;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W7;

    union {
        struct {
            uint8_t commanded_gain31_10ths : 4;
            uint8_t commanded_gain31_100ths : 4;
            bool commanded_gain31_exp_negative : 1;
            uint8_t commanded_gain31_exp : 7;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W8;

    union {
        struct {
            uint8_t commanded_gain32_10ths : 4;
            uint8_t commanded_gain32_100ths : 4;
            bool commanded_gain32_exp_negative : 1;
            uint8_t commanded_gain32_exp : 7;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W9;

    union {
        struct {
            uint8_t commanded_gain33_10ths : 4;
            uint8_t commanded_gain33_100ths : 4;
            bool commanded_gain33_exp_negative : 1;
            uint8_t commanded_gain33_exp : 7;
        } __attribute__((__packed__)) data;
        uint16_t raw;
    } W10;
} __attribute__((__packed__));

struct CORALS_5R {} __attribute__((__packed__));

struct CORALS_5T {} __attribute__((__packed__));

} // end namespace Messages
} // end namespace CORALS

#endif // __CORALS_MESSAGES_HPP__