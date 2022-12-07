#include <MIDI.h>
#include "RBConfiguration.h"
#pragma GCC diagnostic error "-Wextra"

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

static constexpr output_conf_t outputs[NUM_OUT] = {
    [OUT_KICK] = {.pin = 3, .timing = &kickTiming},
    [OUT_PAD_RED] = {.pin = 6, .timing = &padTiming},
    [OUT_PAD_YELLOW] = {.pin = 9, .timing = &padTiming},
    [OUT_PAD_BLUE] = {.pin = 10, .timing = &padTiming},
    [OUT_PAD_GREEN] = {.pin = 2, .timing = &padTiming},
    [OUT_CYM_YELLOW] = {.pin = 16, .timing = &cymTiming},
    [OUT_CYM_BLUE] = {.pin = 17, .timing = &cymTiming},
    [OUT_CYM_GREEN] = {.pin = 4, .timing = &cymTiming},

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

static output_state_t outputStates[NUM_OUT];

// this works reasonably well, but could use some refinement. maybe keep a
// buffer of recent notes instead. that way we could turn flams and such into
// R+Y hits and so on. maybe consider velocity, too. turning this into mostly
// configuration data might be nice, also.
static bool outputForNote(const uint8_t &note, output_t &out)
{
    switch (note)
    {
#define MIDI_MAP(midi_note, rb_out) \
    case midi_note:                 \
        out = rb_out;               \
        break;
#include "MidiMapping.tbl"
#undef MIDI_MAP
    default:
        return false;
    }
    return true;
}

static void writeOutput(const output_t &out, const bool &state)
{
    digitalWrite(outputs[out].pin, state);
    outputStates[out].triggered = state;
}

static void noteOn([[maybe_unused]] const uint8_t &channel, const uint8_t &note, const uint8_t &velocity)
{
    if (velocity <= SENSITIVITY)
        return;
    output_t out;
    if (!outputForNote(note, out))
        return;

    auto io = &outputs[out];
    auto st = &outputStates[out];
    auto t = millis();
    if (t - st->triggeredAt > io->timing->hold + io->timing->holdOff)
    {
        writeOutput(out, HIGH);
        st->triggeredAt = t;
    }
}

MIDI_CREATE_DEFAULT_INSTANCE()

void setup()
{
    for (int out = FIRST_OUT; out < NUM_OUT; out++)
    {
        pinMode(outputs[out].pin, OUTPUT);
        writeOutput(static_cast<output_t>(out), LOW);
    }
    MIDI.begin(MIDI_CHANNEL);
}

void loop()
{
    while (MIDI.read())
    {
        // you can technically add a note ON handler in the midi library, but i like this better
        auto location_byte = MIDI.getType();
        auto channel = MIDI.getChannel();
        auto note = MIDI.getData1();
        auto velocity = MIDI.getData2();
        if (location_byte == midi::MidiType::NoteOn)
            noteOn(channel, note, velocity);
    }
    auto t = millis();
    for (auto out = 0; out < NUM_OUT; out++)
    {
        if (outputStates[out].triggered && t - outputStates[out].triggeredAt > outputs[out].timing->hold)
            writeOutput((output_t)out, LOW);
    }
}
