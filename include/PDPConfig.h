#include "RBShared.h"

enum output_t
{
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
};

static constexpr output_conf_t outputs[NUM_OUT] = {
    [OUT_KICK] = {.pin = 2, .timing = &kickTiming},
    [OUT_PAD_RED] = {.pin = A0, .timing = &padTiming},
    [OUT_PAD_YELLOW] = {.pin = A1, .timing = &padTiming},
    [OUT_PAD_BLUE] = {.pin = A2, .timing = &padTiming},
    [OUT_PAD_GREEN] = {.pin = A3, .timing = &padTiming},
    [OUT_CYM_YELLOW] = {.pin = 3, .timing = &cymTiming},
    [OUT_CYM_BLUE] = {.pin = 4, .timing = &cymTiming},
    [OUT_CYM_GREEN] = {.pin = 5, .timing = &cymTiming},
};

// No need to invert state for PDP board
bool ReturnTriggeredState(const output_t &out, const bool &state)
{
    return state;
}

bool ActivatePin(const output_t &out)
{
    return HIGH;
}

bool DeactivatePin(const output_t &out)
{
    return LOW;
}
