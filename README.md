# Smart-Trolley-System-ESP32-RFID
# 🛒 Smart Trolley System Using ESP32 and RFID

A smart shopping trolley system developed using **ESP32 and RFID technology** to automate product identification, calculate the shopping bill in real time, and help users manage their shopping budget.

The system integrates an **ESP32 microcontroller, MFRC522 RFID reader, RFID tags, 16x2 I2C LCD, 4x4 keypad, servo motor, buzzer, and Bluetooth communication**.

---

## 📌 Project Overview

In traditional supermarket shopping, customers need to wait at billing counters and may not know their total expenditure while shopping.

This project aims to solve these problems by providing a smart trolley that:

- Identifies products using RFID tags
- Calculates the total bill automatically
- Allows users to set a shopping budget
- Displays product and billing information on an LCD
- Alerts the user when the budget is exceeded
- Sends billing information through Bluetooth
- Uses a servo motor for a smart trolley lid mechanism

The ESP32 acts as the central controller and manages all the connected components.

---

## 🚀 Features

- 🔹 RFID-based product identification
- 🔹 Automatic bill calculation
- 🔹 Real-time total cost display
- 🔹 User-defined shopping budget
- 🔹 Budget exceeded warning using buzzer
- 🔹 LCD-based user interface
- 🔹 Bluetooth-based bill transmission
- 🔹 Servo motor controlled trolley lid
- 🔹 Keypad-based budget entry
- 🔹 Predefined product database

---

## 🧠 Working Principle

The system works through the following process:

```text
                ┌──────────────────┐
                │   User Sets      │
                │     Budget       │
                └────────┬─────────┘
                         │
                         ▼
                ┌──────────────────┐
                │      ESP32       │
                └────────┬─────────┘
                         │
                         ▼
                ┌──────────────────┐
                │   RFID Reader    │
                │    MFRC522       │
                └────────┬─────────┘
                         │
                         ▼
                ┌──────────────────┐
                │ Read RFID UID    │
                └────────┬─────────┘
                         │
                         ▼
                ┌──────────────────┐
                │ Match Product    │
                │    Database      │
                └────────┬─────────┘
                         │
                         ▼
                ┌──────────────────┐
                │ Get Name & Price │
                └────────┬─────────┘
                         │
                         ▼
                ┌──────────────────┐
                │ Update Total Bill│
                └────────┬─────────┘
                         │
             ┌───────────┼────────────┐
             ▼           ▼            ▼
          ┌──────┐   ┌────────┐   ┌─────────┐
          │ LCD  │   │ Buzzer │   │Bluetooth│
          └──────┘   └────────┘   └─────────┘
                         │
                         ▼
                  Budget Exceeded?
                         │
                   ┌─────┴─────┐
                   │           │
                  YES          NO
                   │           │
                   ▼           ▼
                Warning     Continue
