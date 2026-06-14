#include "hub.h"
#include "DoorLock.h"
#include "buttons.h"

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
    b.Menu("Защёлка;Подсветка;Отладка ввода/вывода");

    // === Menu 0 ===
    b.show(b.menu() == 0);

    {
        gh::Row r(b);
        b.LED_("door_closed_led", &lock.locked).label("Closed"); {
            gh::Col c(b);
            if (b.Button().label("Open").icon("f3c1").click()) {
                lock.setState(false);
                if (b.build.client.connection() == gh::Connection::HTTP) {
                    hub.sendRefresh();
                } else
                    hub.update("door_closed_led").value(lock.locked);
            }
            if (b.Button().label("Close").icon("f023").click()) {
                lock.setState(true);
                if (b.build.client.connection() == gh::Connection::HTTP) {
                    hub.sendRefresh();
                } else
                    hub.update("door_closed_led").value(lock.locked);
            }
        }
    }

    // === Menu 1 ===
    b.show(b.menu() == 1);


    // === Menu 2 ===
    // Input debug
    b.show(b.menu() == 2);
    {
        b.Title("Ввод:");
        {
            gh::Row r(b);
            bool left_bnt_press = buttons::left_rot_btn.pressing();
            b.LED_("left_btn_state", &left_bnt_press).label("Left rotation");
            bool right_bnt_press = buttons::right_rot_btn.pressing();
            b.LED_("right_btn_state", &right_bnt_press).label("Right rotation");
            bool builtin_btn_press = buttons::builtin_btn.pressing();
            b.LED_("builtin_btn_state", &builtin_btn_press).label("Builtin button");
        }
        b.Title("Вывод:");
        b.LED_("lock_state_led", &lock.locked).label("Lock");
    }
}
