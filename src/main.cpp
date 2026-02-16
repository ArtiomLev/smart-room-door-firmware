#include "Arduino.h"
#include "NodeMCU_v3_pin.h"
#include "config.h"

// =====================================================================================================================
// Libs
// ---------------------------------------------------------------------------------------------------------------------

#include "ESP8266WiFi.h"

#include <GyverHub.h>
GyverHub hub("MyDevices", "Door", "f52a"); // имя сети, имя устройства, иконка

#include "SoftwareSerial.h"
SoftwareSerial HubSerial(HUB_SERIAL_RX,HUB_SERIAL_TX); // Software serial for GyverHUB

#include "FastLED.h"
CRGB leds[LEDS_NUM];

#include "EncButton.h"
Button builtin_btn(BUILTIN_BUTTON);
Button left_rot_btn(LEFT_ROT_BTN);
Button right_rot_btn(RIGHT_ROT_BTN);

// =====================================================================================================================
// Classes
// ---------------------------------------------------------------------------------------------------------------------

#include "DoorLock.h"
DoorLock lock(DOOR_LOCK_PIN);

// =====================================================================================================================
// Variables
// ---------------------------------------------------------------------------------------------------------------------


// =====================================================================================================================

void build(gh::Builder &b);

// =====================================================================================================================
// Code
// ---------------------------------------------------------------------------------------------------------------------

void setup() {
    // Настройка пинов
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    pinMode(LED_PIN, OUTPUT);

    // Инициализация UART
    Serial.begin(115200);
    Serial.println();

    // Инициализация ленты в FastLED
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LEDS_NUM);

    // Лента синим
    for (byte i = 0; i < LEDS_NUM; i++) {
        leds[i] = CRGB::Blue;
    }
    FastLED.setBrightness(50);
    FastLED.show();
    delay(500);

    // Инициализация и подключение к сети WiFI
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to \"");
    Serial.print(WIFI_SSID);
    Serial.println("\":");
    while (WiFi.status() != WL_CONNECTED) {
        delay(200);
        Serial.print(".");
    }
    Serial.println("\nConnected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    // Инициализация GyverHUB
    hub.stream.config(&HubSerial, gh::Connection::Serial);
    //hub.stream.config(&Serial, gh::Connection::Serial);
    hub.onBuild(build); // подключение билдера
    hub.begin();


    for (byte i = 0; i < LEDS_NUM; i++) {
        leds[i] = CRGB::Red;
    }
    FastLED.setBrightness(10);
    FastLED.show();
}

void loop() {
    builtin_btn.tick();
    left_rot_btn.tick();
    right_rot_btn.tick();

    if (builtin_btn.click()) {
        lock.toggle();
        hub.sendUpdate("door_closed_led");
        Serial.println("Switch!");
    }
    Serial.printf("LIB\t"
                  "Lock: %d\t"
                  "Button: %d\t"
                  "Left: %d\t"
                  "Right: %d\t\n",
                  lock.getState(),
                  builtin_btn.pressing(),
                  left_rot_btn.pressing(),
                  right_rot_btn.pressing());

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
        digitalWrite(LED_BUILTIN, !lock.getState());

    hub.tick();
}

void build(gh::Builder &b) {
    {
        gh::Row r(b);
        b.LED_("door_closed_led", &lock.locked).label("Closed"); {
            gh::Col c(b);
            if (b.Button().label("Open").icon("f3c1").click()) {
                lock.setState(false);
                hub.update("door_closed_led").value(lock.locked);
            }
            if (b.Button().label("Close").icon("f023").click()) {
                lock.setState(true);
                hub.update("door_closed_led").value(lock.locked);
            }
        }
    }
}
