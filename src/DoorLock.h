#pragma once
#include "Arduino.h"

class DoorLock {
    byte pin; // Door lock control pin

public:
    bool locked; // Door lock state

    explicit DoorLock(const byte pin, const bool start_state = false) : pin(pin) {
        pinMode(pin, OUTPUT);
        setState(start_state);
    }

    /// Set door lock state
    bool setState(const bool state) {
        if (state == getState()) return false;
        locked = state;
        digitalWrite(pin, state);
        Serial.print("Set lock state to ");
        Serial.println(state);
        return true;
    }

    /// Toggle door lock state
    void toggle() { setState(!getState()); }
    /// Get door lock state
    bool getState() const { return locked; }
};
