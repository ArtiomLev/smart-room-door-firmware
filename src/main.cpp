#include "NodeMCU_v3_pin.h"
#include "config.h"
#include "Arduino.h"

// =====================================================================================================================
// Libs
// ---------------------------------------------------------------------------------------------------------------------

#include "EncButton.h"
Button builtin_btn(BUILTIN_BUTTON);
Button left_rot_btn(LEFT_ROT_BTN);
Button right_rot_btn(RIGHT_ROT_BTN);

// =====================================================================================================================
// Modules
// ---------------------------------------------------------------------------------------------------------------------

#include "DoorLock.h"
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
    builtin_btn.tick();
    left_rot_btn.tick();
    right_rot_btn.tick();

    if (builtin_btn.click()) {
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
                      builtin_btn.pressing(),
                      left_rot_btn.pressing(),
                      right_rot_btn.pressing());
    }

    led::tick();

    hub::tick();
}
