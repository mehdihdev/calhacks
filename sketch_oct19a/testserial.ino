//Liquid Crystal LCD
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "printf.h"


LiquidCrystal_I2C lcd(0x27,16,2);


//RF Transmitter:
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


const int radioCSPin = 10;
RF24 radio(2, radioCSPin); // CE, CSN
const byte address[6] = "00001";


//RFID Scanner
#include <MFRC522.h>
const int rfidCSPin = 4;
MFRC522 mfrc522(rfidCSPin, 3); //CS, RST


void lcdStart() {
  lcd.init();
  lcd.backlight();
  lcd.begin(16,2);
}


void message(String line1, String line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}


void startTransmitter() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}


void transmitSuccess() {
  const char text[] = "Success";
  radio.write(&text, sizeof(text));
}


void transmitFailure() {
  const char text[] = "Failure";
  radio.write(&text, sizeof(text));
}


void rfidScan() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }


  String content= "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
      // RFID Scanner Inactive, RF Transmitter Active
    digitalWrite(rfidCSPin, HIGH);   // Disable RFID
    digitalWrite(radioCSPin, LOW);   // Enable RF24
    delay(100);
  
  startTransmitter();
  if (content.substring(1) == "2E D2 2F 03")
  {

    transmitSuccess();
    lcd.clear();
    lcd.print("Welcome Mehdi");
  }
  else if (content.substring(1) == "96 8D 0D 01")
  {
    transmitSuccess();
    lcd.clear();
    lcd.print("Welcome Jonathan");
  }
  else {
    transmitFailure();
    lcd.clear();
    lcd.print("Access Denied.");
  }
  digitalWrite(rfidCSPin, LOW);    // Enable RFID
  digitalWrite(radioCSPin, HIGH);  // Disable RF24
}




void setup() {
  Serial.begin(9600);  
  SPI.begin();
  pinMode(radioCSPin, OUTPUT);
  pinMode(rfidCSPin, OUTPUT);
  digitalWrite(radioCSPin, HIGH);
  digitalWrite(rfidCSPin, LOW);

  lcdStart();
  mfrc522.PCD_Init();
  startTransmitter();

  message("Enter your card", "to continue.");
}


void loop() {
  // RFID Scanner Active
  digitalWrite(rfidCSPin, LOW);    // Enable RFID
  digitalWrite(radioCSPin, HIGH);  // Disable RF24
 
  rfidScan();  // Scan for RFID cards
 
  // RFID Scanner Inactive, RF Transmitter Active
  digitalWrite(rfidCSPin, HIGH);   // Disable RFID
  digitalWrite(radioCSPin, LOW);   // Enable RF24
 
  // Transmit data using RF24
  transmitSuccess();
  //transmitFailure();
}


