**NOTE: THIS PROJECT HAS BEEN SUPERSEDED BY [OPENRB](https://github.com/delabrcd/openrb-instruments) AND IS NO LONGER THE RECOMMENDED SOLUTION FOR AN XBOX MIDI ADAPTER**

# Rockband 4 Midi Drums
 an adaptation of [rockbend](https://github.com/rafl/diy-rockband/tree/master/rockbend) with off-the-shelf parts

# Table of Contents
- [Rockband 4 Midi Drums](#rockband-4-midi-drums)
- [Table of Contents](#table-of-contents)
- [Parts](#parts)
  - [Necessary Parts](#necessary-parts)
  - [Tools](#tools)
  - [Optional Parts](#optional-parts)
  - [Notes about Parts](#notes-about-parts)
- [How To Assemble](#how-to-assemble)
  - [Making The Wires](#making-the-wires)
  - [Midi Shield Pinout](#midi-shield-pinout)
  - [Attaching everything together](#attaching-everything-together)
  - [My MIDI Shield](#my-midi-shield)
  - [Cable for Cymbals](#cable-for-cymbals)
  - [Cable for Pads](#cable-for-pads)
  - [My final assembly - cover off](#my-final-assembly---cover-off)
  - [My final assembly - cover on](#my-final-assembly---cover-on)
  - [Customizing the Code](#customizing-the-code)
- [Programming Your Arduino](#programming-your-arduino)
- [Troubleshooting](#troubleshooting)
  - [I wired everything up but my controller won't turn on!](#i-wired-everything-up-but-my-controller-wont-turn-on)
  - [Nothing is happening after I plugged everything in and play notes on my drums](#nothing-is-happening-after-i-plugged-everything-in-and-play-notes-on-my-drums)

# Parts
## Necessary Parts 
- [Arduino Uno](https://www.amazon.com/Arduino-A000066-ARDUINO-UNO-R3/dp/B008GRTSV6) or any clone
- Any arduino [midi shield](https://www.amazon.com/Comimark-Breakout-Arduino-Digital-Interface/dp/B07X44L1T4/ref=dp_fod_1?pd_rd_i=B07X44L1T4&psc=1)
- [24 or 26 AWG Wire](https://www.amazon.com/dp/B089CHVN7G?ref=ppx_yo2ov_dt_b_product_details&th=1) multiple colors is a plus for less confusion, but not necessary
- 5 JST 2.0 2 pin male connectors
- 1 JST 2.0 5 pin male connector 
- [Midi Cable](https://www.amazon.com/dp/B009GUP7U8?psc=1&ref=ppx_yo2ov_dt_b_product_details)
- [USB A -> B cable](https://www.amazon.com/AmazonBasics-USB-2-0-Cable-Male/dp/B00NH11KIK/ref=sr_1_3?crid=3C7VI85EACIL9&keywords=usb+a+to+b&qid=1662131751&sprefix=usb+a+to+b%2Caps%2C120&sr=8-3) (most arduino's will come with one of these)

## Tools
- Soldering Iron with precision tip  
- JST Crimpers
- Wire Strippers
- Computer running [VSCode](https://code.visualstudio.com/) w/ the [PlatformIO](https://platformio.org/) extension installed

## Optional Parts
- 3 JST 2.54 Male & Female Pair (instead of soldering the wires directly to the midi shield)

## Notes about Parts
- I bought this [kit](https://www.amazon.com/dp/B09Q5G8DVB?psc=1&ref=ppx_yo2ov_dt_b_product_details) with all the JST things I needed, crimpers included. It was definitely nice not having to worry if I messed up a crimp or two - I definitely recommend getting extra. 
- There are premade JST 2.0 connectors with wires already crimped into them - these may be worth looking into if you dont want to bother with buying the crimping tool and a ton of connectors you'll never use but you'll then need to solder your wires directly to the midi shield which can be a huge pain - especially if you aren't comfortable soldering

# How To Assemble
 
## Making The Wires
 Cut some wires and get crimping, here's the pinout that I used, feel free to adjust however you want, but you'll need to update the code accordingly. Make sure you pay attention to which pin each wire is going into.  The kick and cymbal connectors both don't have grounding, this is intentional. The pads do have a neutral wire, pay attention to the polarity of these connectors. (Theoretically this entire thing would work with only one common ground going through the power supply but there isn't a 3.3V pin on the particular midi shield I used so it wasn't convenient to use the arduino to power the board)

This is the configuration found in `main.cpp` you can leave it like I have it and use my pins or modify it before you flash your UNO.


```
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
```

| Wire Color| RB Function   | Arduino Pin   |
| ----------| -----------   | -----------   |
| White     | N/A (Ground)  | GND           |
| Red       | Kick          | 2             |
| Yellow (5pin)| Y Cym | 3 |
| Blue (5pin)| B Cym | 4 |
| Green (5pin) | G Cym | 5| 
| Black (2pin) | R Pad | A0 |
| Yellow (2pin) | Y Pad | A1 |
| Blue (2pin) | B Pad | A2 |
| Green (2pin) | G Pad | A3 |

![drum board picture with labels](https://bitbucket.org/delabrcd/drum-images/raw/master/drum_board.jpg)

## Midi Shield Pinout
![midi shield pinout](https://bitbucket.org/delabrcd/drum-images/raw/master/midi_shield.jpg) 


## Attaching everything together

Following whatever pinout you decide, either solder the cables to the shield directly (not recommended) or solder some 2.54mm headers to the shield and crimp the ends onto them. My setup is like this:

## My MIDI Shield
- Top Connector - Kick and Cymbals 
- Middle Connector - Ground
- Bottom Connector - Pads
  
![my midi shield](https://bitbucket.org/delabrcd/drum-images/raw/master/my_midi_shield.jpg)

## Cable for Cymbals
![my cymbal cable](https://bitbucket.org/delabrcd/drum-images/raw/master/my_cymbal_cable.jpg)

## Cable for Pads
![my pads cable](https://bitbucket.org/delabrcd/drum-images/raw/master/my_pads_cable.jpg)

## My final assembly - cover off
Make sure to plug your "connect" button and the battery pack back into the drum board
![my final assembly cover off](https://bitbucket.org/delabrcd/drum-images/raw/master/my_final_assembly_cover_off.jpg)
## My final assembly - cover on
I cut a small hole in the side of my cover to route the cables out through. 
![my final assembly cover on](https://bitbucket.org/delabrcd/drum-images/raw/master/my_final_assembly_cover_on.jpg)

## Customizing the Code
Assuming you have already downloaded the repo and have it open in VSCode / PlatformIO 

Open `include/MidiMapping.tbl`, customize what midi notes you want to trigger each pad, I've provided my configuration.  If you want to add more notes, just add another `MIDI_MAP(midi_note_input, rb_drums_out)` make sure to use one of the following options as your `rb_drums_out`. 

A great way to tell which midi notes are coming from your drum brain is with [Midi View](https://hautetechnique.com/midi/midiview/)
```   
OUT_PAD_RED,
OUT_PAD_YELLOW,
OUT_PAD_BLUE,
OUT_PAD_GREEN,
OUT_CYM_YELLOW,
OUT_CYM_BLUE,
OUT_CYM_GREEN,
```

Open `include/RBConfiguration.h` to find the specific timings for each pad, how long it should be held on and time between presses.  This works relatively well for me, but I'm also not playing incredibly advanced tracks so success may vary. 

Change `MIDI_CHANNEL` to what channel you'd like to be listening on. 
```
// Listen on midi channel 10
constexpr unsigned int MIDI_CHANNEL = 10;
```

```
// Listen on all midi channels
constexpr unsigned int MIDI_CHANNEL = 0;
```

Change `SENSITIVITY` to whatever your desired minimum Midi velocity is.  If you're unsure about this number, you can always set it to 0 and that will allow every note through. 

# Programming Your Arduino 
Once the code is modified to your liking, go ahead and upload it to your arduino.  If you don't have experience doing this, I'd recommend looking up a proper introductory guide since they will do a much more thourough job of explaining the process than I will here. 

You'll need to make sure the ON/OFF switch on the midi shield is set to the OFF position while you're programming since there is only one serial connection on the UNO and that will be used for both programming and MIDI.  Switch it back to the ON position to be able to use MIDI. ****

# Troubleshooting
## I wired everything up but my controller won't turn on!
Make sure you've programmed the UNO and your pinout is correct - if a pin is unconfigured on the arduino it could be causing a multitude of problems.  

If you've already done this, unplug all of the cables you made from the drum controller and try to turn it on.  If it turns on without any of your cables plugged in, chances are you wired it wrong. Double check everything.

## Nothing is happening after I plugged everything in and play notes on my drums
The first thing to check is if your arduino has an RX connection.  There are 3 yellow LED's on the UNO all next to each other.  One will light up when you plug it in or reset it, this is connected to pin 13.  Then there are the 2 LEDs next to it, if your 'duino is recieving midi signal, the RX light will be ON and the TX light will be off. 

**If your RX light *is not* on** make sure:
- you have the midi cable plugged into the "IN" midi port
- your drums are setup to output midi on the channel you selected 
- the switch on the shield is set to ON
  
If this still isn't the case you can try: 
- resetting the arduino with the button on the shield
- reprogramming the arduino 
- power cycling the arduino 

**If your RX light *is* on**, that means your arduino has established a midi connection with your drums. Make sure your pinouts going to your controller are correct and that your controller is on. 
