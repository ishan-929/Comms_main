#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0xF4, 0x2D, 0xC9, 0x6B, 0x07, 0x68};

int microphonePin = 5;

typedef struct struct_message {
    bool microphoneValue;
} struct_message;

struct_message myData;

esp_now_peer_info_t peerInfo;

void setup() {
    Serial.begin(152000);
    pinMode(microphonePin,INPUT);
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
}

void loop() {
    myData.microphoneValue = digitalRead(microphonePin);
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    delay(55);
}

