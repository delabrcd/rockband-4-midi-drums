#pragma once
#include <stdint.h>
#include <stdlib.h>

enum output_t {
    FIRST_OUT,
    OUT_KICK = FIRST_OUT,
    OUT_PAD_RED,
    OUT_PAD_YELLOW,
    OUT_PAD_BLUE,
    OUT_PAD_GREEN,
    OUT_CYM_YELLOW,
    OUT_CYM_BLUE,
    OUT_CYM_GREEN,
    LAST_OUT = OUT_CYM_GREEN,
    NUM_OUT,
    NO_OUT,
};

struct output_timing_t {
    typedef uint8_t milliseconds;

    const milliseconds hold;     //
    const milliseconds holdOff;  // useconds
};

struct output_conf_t {
    const uint8_t          pin;
    const output_timing_t *timing;
    const bool             activeLow;
};

struct output_state_t {
    typedef uint32_t milliseconds;

    output_state_t() {
        triggeredAt = 0;
        triggered   = false;
    }

    milliseconds triggeredAt;
    bool         triggered;
};