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
const byte address[6] = "00005";

//RFID Scanner
#include <MFRC522.h>
const int rfidCSPin = 4;
MFRC522 mfrc522(rfidCSPin, 3); //CS, RST

String ids[] = {"2E D2 2F 03","","","","","","","","","","","","","","","","","","","","","","","",""};

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

void transmit(String data) {
  const char* text = data.c_str();
  radio.write(text, strlen(text) + 1);
}

bool isClient(String element) {
  int numElements = sizeof(ids) / sizeof(ids[0]);
  for (int i = 0; i < numElements; i++) {
    if (ids[i] == element.substring(1)) {
      return true;
    }
  }
  return false;
}

String rfidScanLite() {
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return "Default";
  }
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return "Default";
  }

  String content= "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  if (isClient(content)) {
    return "Success";
  }
  else {
    return "Failure";
  }  
}

void addNewCard() {
  delay(2000);
  String data = "Default";
  while(data == "Default") {
    data = rfidScanLite();
  }
  String content= "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  int numElements = sizeof(ids) / sizeof(ids[0]);
  for (int i = 0; i < numElements; i++) {
    if (ids[i] == "") {
      ids[i] = content.substring(1);
      message("New Card Added","");
      break;
    }
    message("New Card failed", "to add");
  }
}

String rfidScan(bool newCard) {
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return "Default";
  }
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return "Default";
  }

  String content= "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  if (newCard) {
    if (isClient(content)) {
      message("Tap New Card to","Register Card");
      addNewCard();
      return "Default";
    }
    else {
      message("You do not have"," this permission");
      return "Default";
    }
  }
  else {
    if (isClient(content)) {
      message("Welcome Home","");
      return "Success";
    }
    else {
      message("Access Denied","");
      return "Failure";
    }  
  }
}


void setup() {
  Serial.begin(9600);  
  SPI.begin();
  pinMode(radioCSPin, OUTPUT);
  pinMode(rfidCSPin, OUTPUT);
  pinMode(6, INPUT_PULLUP);
  digitalWrite(radioCSPin, HIGH);
  digitalWrite(rfidCSPin, LOW);

  mfrc522.PCD_Init();
  startTransmitter();
  lcdStart();

  message("Tap your card", "to continue.");
  //printf_begin();
  //radio.printDetails();
}

void loop() {
  digitalWrite(rfidCSPin, LOW);    // Enable RFID
  digitalWrite(radioCSPin, HIGH);  // Disable RF24
  delay(100);
  
  String msg;
  if(digitalRead(6) == 0) {
    rfidScan(true);
  }
  else {
    msg = rfidScan(false);
  }

  digitalWrite(rfidCSPin, HIGH);   // Disable RFID
  digitalWrite(radioCSPin, LOW);   // Enable RF24

  if (msg != "Default") {
    transmit(msg);
    delay(3000);
    message("Tap your card", "to continue.");
  }
}