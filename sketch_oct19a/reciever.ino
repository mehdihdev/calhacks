//Credit to Dejan Nedelkovski, www.HowToMechatronics.com, for part of this code

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00005";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
    if (strcmp(text, "Success") == 0) {
      digitalWrite(3, HIGH);
      delay(2500);
      digitalWrite(3, LOW);
    }
    else if (strcmp(text, "Failure") == 0) {
      digitalWrite(2, HIGH);
      delay(2500);
      digitalWrite(2, LOW);
    }
  }
}