#include "led.h"

CRGB led::leds[LEDS_NUM];


void led::setup() {
    // Инициализация ленты в FastLED
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LEDS_NUM);
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
