#include "NodeMCU_v3_pin.h"
#include "config.h"
#include "Arduino.h"

// =====================================================================================================================
// Libs
// ---------------------------------------------------------------------------------------------------------------------


// =====================================================================================================================
// Modules
// ---------------------------------------------------------------------------------------------------------------------

#include "DoorLock.h"
#include "buttons.h"
#include "hub.h"
#include "led.h"

// =====================================================================================================================
// Variables
// ---------------------------------------------------------------------------------------------------------------------


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

    hub::setup();

    led::setup();

}

void loop() {
    buttons::tick();

    if (buttons::builtin_btn.click()) {
        lock.toggle();
        hub::hub.sendUpdate("door_closed_led");
        Serial.println("Switch!");
    }

    static unsigned long state_log_tmr = millis();
    if (millis() - state_log_tmr > 500) {
        state_log_tmr = millis();
        digitalWrite(LED_BUILTIN, !lock.getState());
        Serial.printf("LIB\t"
                      "Lock: %d\t"
                      "Button: %d\t"
                      "Left: %d\t"
                      "Right: %d\t\n",
                      lock.getState(),
                      buttons::builtin_btn.pressing(),
                      buttons::left_rot_btn.pressing(),
                      buttons::right_rot_btn.pressing());
    }

    led::tick();

    hub::tick();
}
