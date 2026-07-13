#include <Arduino.h>

int microphonePin = 5;
int ledPin = 23;
int microphoneValue;

void setup() {
    pinMode(microphonePin, INPUT);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    digitalWrite(microphonePin,LOW);
}

void loop() {
    microphoneValue = digitalRead(microphonePin);
    if (microphoneValue == HIGH) {
        digitalWrite(ledPin,HIGH);
        delay(500);
    }
    else {
        digitalWrite(ledPin,LOW);
    }
}
