// Only uncomment this if you're using MadCatz brain
// #define MADCATZ_CONFIG
// Uncomment this if you want to use your drum kit like the toy drum
// #define USE_RB_DRUM_CONFIG
#ifndef MADCATZ_CONFIG
#include "PDPConfig.h"
#else
#include "MadCatzConfig.h"
#endif
#pragma GCC diagnostic error "-Wextra"

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
    outputStates[out].triggered = ReturnTriggeredState(out, state);
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
        writeOutput(out, ActivatePin(out));
        st->triggeredAt = t;
    }
}

MIDI_CREATE_DEFAULT_INSTANCE()

void setup()
{
    for (int out = FIRST_OUT; out < NUM_OUT; out++)
    {
        pinMode(outputs[out].pin, OUTPUT);
        output_t castOut = static_cast<output_t>(out);
        writeOutput(castOut, DeactivatePin(castOut));
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
        {
            output_t castOut = static_cast<output_t>(out);
            writeOutput(castOut, DeactivatePin(castOut));
        }
    }
}
