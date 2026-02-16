#pragma once
#include "config.h"

#include "FastLED.h"

namespace led {
    extern CRGB leds[LEDS_NUM];

    void setup();
    void tick();
}