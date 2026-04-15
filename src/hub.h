#pragma once
#include "config.h"

#include <SoftwareSerial.h>
#include <GyverHub.h>

namespace hub {
    extern GyverHub hub;
    extern SoftwareSerial softSerial;

    void setup();
    void tick();
    void builder(gh::Builder &b);
}

#ifdef H
#undef H
#endif