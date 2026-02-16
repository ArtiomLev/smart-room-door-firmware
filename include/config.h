#pragma once

#include "NodeMCU_v3_pin.h"

// Сеть

#define WIFI_SSID "TP-Link_0CAC"
#define WIFI_PASSWORD "79574822"

// Выводы

#define DOOR_LOCK_PIN D0_PIN
#define LED_PIN D1_PIN

#define LEFT_ROT_BTN D2_PIN
#define RIGHT_ROT_BTN D5_PIN

#define HUB_SERIAL_RX D6_PIN
#define HUB_SERIAL_TX D7_PIN

// Настройки

#define LEDS_NUM 99
#define BRIGHT 200