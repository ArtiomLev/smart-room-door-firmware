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
    /*// Бегающая точка с затухающиим следом
    static unsigned long effect_tmr = millis();
    if (millis() - effect_tmr >= 50) {
        FastLED.clear();
        static int counter = 0;
        if (counter > LEDS_NUM) counter = 0;
        for (byte i = 0; i <= 6; i++) {
            int led_num = counter + i;
            if (led_num > LEDS_NUM) led_num = led_num - LEDS_NUM;
            leds[counter + i].r = pow(2, i);
            //            leds[counter+i].g = pow(2, i);
            //            leds[counter+i].b = pow(2, i);
        }
        counter++;
        FastLED.show();
        effect_tmr = millis();
    }*/
}
