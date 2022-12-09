#pragma once

#include "RBTimings.hpp"
#include "Arduino.h"

#if defined(FEATHER328)
static constexpr output_conf_t outputs[NUM_OUT] = {
    [OUT_KICK]       = {.pin = 3, .timing = &kickTiming, .activeLow = true},
    [OUT_PAD_RED]    = {.pin = 6, .timing = &padTiming, .activeLow = false},
    [OUT_PAD_YELLOW] = {.pin = 9, .timing = &padTiming, .activeLow = false},
    [OUT_PAD_BLUE]   = {.pin = 10, .timing = &padTiming, .activeLow = false},
    [OUT_PAD_GREEN]  = {.pin = 2, .timing = &padTiming, .activeLow = false},
    [OUT_CYM_YELLOW] = {.pin = 16, .timing = &cymTiming, .activeLow = false},
    [OUT_CYM_BLUE]   = {.pin = 17, .timing = &cymTiming, .activeLow = false},
    [OUT_CYM_GREEN]  = {.pin = 4, .timing = &cymTiming, .activeLow = false},
};
#elif defined(UNO) 
static constexpr output_conf_t outputs[NUM_OUT] = {
    [OUT_KICK]       = {.pin = 2, .timing = &kickTiming, .activeLow = true},
    [OUT_PAD_RED]    = {.pin = A0, .timing = &padTiming, .activeLow = false},
    [OUT_PAD_YELLOW] = {.pin = A1, .timing = &padTiming, .activeLow = false},
    [OUT_PAD_BLUE]   = {.pin = A2, .timing = &padTiming, .activeLow = false},
    [OUT_PAD_GREEN]  = {.pin = A3, .timing = &padTiming, .activeLow = false},
    [OUT_CYM_YELLOW] = {.pin = 3, .timing = &cymTiming, .activeLow = false},
    [OUT_CYM_BLUE]   = {.pin = 4, .timing = &cymTiming, .activeLow = false},
    [OUT_CYM_GREEN]  = {.pin = 5, .timing = &cymTiming, .activeLow = false},
};
#else 
#pragma error "Current board target not supported"
#endif