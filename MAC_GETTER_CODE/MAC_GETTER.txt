#include <Arduino.h>
#include <WIFI.h>

void setup() {
    Serial.begin(115200);
    delay(1000);
    WiFi.mode(WIFI_STA);
    Serial.println("MAC Address: " + WiFi.macAddress());
}
void loop() {

}