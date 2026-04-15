#include "led.h"

NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart1Ws2812Method> led::strip(LEDS_NUM, LED_PIN);


void led::setup() {
    strip.Begin();
    RgbColor color(0, 0, 200);
    for (uint8_t i = 0; i < LEDS_NUM; i++) {
        strip.SetPixelColor(i, color);
    }
    strip.Show();
}

void led::tick() {
    
}
