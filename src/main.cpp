#include <MIDI.h>
#pragma GCC diagnostic error "-Wextra"
#include "UserConfig.h"

#if defined(PDP_KIT)
#include "PDPOutputs.hpp"
#elif defined(MADCATZ_KIT)
#include "MadCatzOutputs.hpp"
#else
#pragma error "Must define the kit being used"
#endif

static_assert(sizeof(outputs) == sizeof(output_conf_t) * NUM_OUT, "OUTPUTS CONFIGURED WRONG");

static output_state_t outputStates[NUM_OUT];

static output_t outputForNote(const uint8_t &note) {
    switch (note) {
#define MIDI_MAP(midi_note, rb_out) \
    case midi_note:                 \
        return rb_out;

#include "MIDIMaps/MidiMap.h"
#undef MIDI_MAP
        default:
            return NO_OUT;
    }
}

static void writeOutput(const output_t &out, const bool &state) {
    digitalWrite(outputs[out].pin, (outputs[out].activeLow ? !state : state));
    outputStates[out].triggered = state;
}

static void noteOn([[maybe_unused]] const uint8_t &channel, const uint8_t &note,
                   const uint8_t &velocity) {
    if (velocity <= SENSITIVITY)
        return;
    output_t out = outputForNote(note);
    if (out == NO_OUT)
        return;

    auto io = &outputs[out];
    auto st = &outputStates[out];
    auto t  = millis();
    if (t - st->triggeredAt > io->timing->hold + io->timing->holdOff) {
        writeOutput(out, HIGH);
        st->triggeredAt = t;
    }
}

MIDI_CREATE_DEFAULT_INSTANCE()

void setup() {
    for (int out = FIRST_OUT; out < NUM_OUT; out++) {
        pinMode(outputs[out].pin, OUTPUT);
        writeOutput(static_cast<output_t>(out), LOW);
    }
    MIDI.begin(MIDI_CHANNEL);
}

void loop() {
    while (MIDI.read()) {
        // you can technically add a note ON handler in the midi library, but i like this better
        auto location_byte = MIDI.getType();
        auto channel       = MIDI.getChannel();
        auto note          = MIDI.getData1();
        auto velocity      = MIDI.getData2();
        if (location_byte == midi::MidiType::NoteOn)
            noteOn(channel, note, velocity);
    }
    auto t = millis();
    for (auto out = 0; out < NUM_OUT; out++) {
        if (outputStates[out].triggered &&
            t - outputStates[out].triggeredAt > outputs[out].timing->hold)
            writeOutput(static_cast<output_t>(out), LOW);
    }
}
