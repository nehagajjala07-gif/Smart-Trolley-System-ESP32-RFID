#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <ESP32Servo.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// RFID
#define SS_PIN 5
#define RST_PIN 22
MFRC522 mfrc522(SS_PIN, RST_PIN);

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Servo
Servo myServo;
#define SERVO_PIN 4

// Budget
int budget = 0;
int total = 0;

// Keypad
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {32, 33, 25, 26};
byte colPins[COLS] = {27, 14, 12, 13};

Keypad keypad = Keypad(
  makeKeymap(keys),
  rowPins,
  colPins,
  ROWS,
  COLS
);

// Product database
struct Product {
  String uid;
  String name;
  int price;
};

Product products[] = {
  {"12345678", "Milk", 50},
  {"87654321", "Bread", 30},
  {"11223344", "Rice", 80}
};

int numProducts = 3;

// Get RFID UID
String getUID() {
  String content = "";

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content += String(mfrc522.uid.uidByte[i], HEX);
  }

  content.toUpperCase();

  return content;
}

// Find product
int findProduct(String uid) {

  for (int i = 0; i < numProducts; i++) {

    if (products[i].uid == uid) {
      return i;
    }
  }

  return -1;
}

// Set shopping budget
void setBudget() {

  lcd.clear();
  lcd.print("Set Budget:");

  String input = "";

  while (true) {

    char key = keypad.getKey();

    if (key) {

      if (key == '#') {
        break;
      }

      if (isdigit(key)) {

        input += key;

        lcd.setCursor(0, 1);
        lcd.print(input);
      }
    }
  }

  budget = input.toInt();

  lcd.clear();
  lcd.print("Budget Set:");

  lcd.setCursor(0, 1);
  lcd.print(budget);

  delay(2000);
}

// Open and close trolley lid
void openLid() {

  myServo.write(90);

  delay(3000);

  myServo.write(0);
}

// Send bill through Bluetooth
void sendBill(String item, int price) {

  SerialBT.println("Item: " + item);
  SerialBT.println("Price: " + String(price));
  SerialBT.println("Total: " + String(total));
  SerialBT.println("----------------");
}

// Setup
void setup() {

  Serial.begin(115200);

  SerialBT.begin("SmartTrolley");

  SPI.begin();

  mfrc522.PCD_Init();

  lcd.init();
  lcd.backlight();

  myServo.attach(SERVO_PIN);

  myServo.write(0);

  lcd.print("Smart Trolley");

  delay(2000);

  setBudget();
}

// Main loop
void loop() {

  // Check for RFID card
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String uid = getUID();

  int index = findProduct(uid);

  if (index != -1) {

    String name = products[index].name;
    int price = products[index].price;

    // Update total
    total += price;

    // Display product
    lcd.clear();

    lcd.print(name);

    lcd.setCursor(0, 1);

    lcd.print("Total: " + String(total));

    // Send bill through Bluetooth
    sendBill(name, price);

    // Open trolley lid
    openLid();

    // Budget warning
    if (total > budget) {

      lcd.clear();

      lcd.print("Over Budget!");

      delay(2000);
    }

  } else {

    lcd.clear();

    lcd.print("Unknown Item");
  }

  delay(1500);
}
