#pragma once
#include <stdint.h>
#include "RBTypes.h"

// timings to hold notes on and off (milliseconds)
constexpr uint8_t KICK_HOLD_ON  = 30;
constexpr uint8_t KICK_HOLD_OFF = 50;

constexpr uint8_t PADS_HOLD_ON  = 10;
constexpr uint8_t PADS_HOLD_OFF = 40;

constexpr uint8_t CYM_HOLD_ON  = 25;
constexpr uint8_t CYM_HOLD_OFF = 40;

// midi channel to listen on
constexpr uint8_t MIDI_CHANNEL = 10;

// midi sensitivity
constexpr uint8_t SENSITIVITY = 10;

static constexpr output_timing_t kickTiming = {.hold = KICK_HOLD_ON, .holdOff = KICK_HOLD_OFF};
static constexpr output_timing_t padTiming  = {.hold = PADS_HOLD_ON, .holdOff = PADS_HOLD_OFF};
static constexpr output_timing_t cymTiming  = {.hold = CYM_HOLD_ON, .holdOff = CYM_HOLD_OFF};
