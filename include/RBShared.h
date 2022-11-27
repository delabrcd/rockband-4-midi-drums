#pragma once
#include <MIDI.h>
#include "RBConfiguration.h"

struct output_timing_t
{
    const unsigned long hold;    // useconds
    const unsigned long holdOff; // useconds
};

static constexpr output_timing_t kickTiming = {.hold = KICK_HOLD_ON, .holdOff = KICK_HOLD_OFF};
static constexpr output_timing_t padTiming = {.hold = PADS_HOLD_ON, .holdOff = PADS_HOLD_OFF};
static constexpr output_timing_t cymTiming = {.hold = CYM_HOLD_ON, .holdOff = CYM_HOLD_OFF};

struct output_conf_t
{
    const int pin;
    const output_timing_t *timing;
};

struct output_state_t
{
    output_state_t()
    {
        triggeredAt = 0;
        triggered = false;
    }
    unsigned long triggeredAt;
    bool triggered;
};
