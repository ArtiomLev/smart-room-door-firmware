#pragma once
#include "config.h"

#include "NeoPixelBus.h"

namespace led {
    extern NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart1Ws2812Method> strip;

    void setup();
    void tick();
}