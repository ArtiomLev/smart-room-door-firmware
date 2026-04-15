#include "hub.h"
#include "DoorLock.h"

#include "ESP8266WiFi.h"

#include "ArduinoOTA.h"

GyverHub hub::hub("MyDevices", "Door", "f52a"); // имя сети, имя устройства, иконка
SoftwareSerial hub::softSerial(HUB_SERIAL_RX,HUB_SERIAL_TX); // Software serial for GyverHUB

void hub::setup() {
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

    ArduinoOTA.setHostname("DoorControllerESP8266");
    ArduinoOTA.begin();

    // Инициализация GyverHUB
    hub.stream.config(&softSerial, gh::Connection::Serial);
    //hub.stream.config(&Serial, gh::Connection::Serial);
    hub.onBuild(builder); // подключение билдера
    hub.begin();
}

void hub::tick() {
    hub.tick();
    ArduinoOTA.handle();
}

void hub::builder(gh::Builder &b) {
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



