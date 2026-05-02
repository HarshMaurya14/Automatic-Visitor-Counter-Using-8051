# 🔢 Automatic Visitor Counter (8051)

## 📌 Overview

This project is an embedded system that automatically counts the number of people entering and exiting a room using IR sensors and an 8051 microcontroller. The system updates the count in real-time on a 16x2 LCD display and controls a relay-based bulb depending on occupancy.

---

## ⚙️ Features

* Bidirectional visitor counting (Entry & Exit)
* Real-time display on LCD
* Automatic light control using relay
* Interrupt-based sensor detection (INT0 & INT1)
* Prevents negative counting

---

## 🧠 Working Principle

* Two IR sensors are placed at entry and exit.
* When entry sensor triggers → count increments.
* When exit sensor triggers → count decrements.
* If count > 0 → bulb ON
* If count = 0 → bulb OFF

---

## 🔌 Hardware Components

* 8051 Microcontroller
* IR Sensor Modules (2)
* 16x2 LCD Display
* ULN2003 Driver IC
* Relay Module
* Resistors, Potentiometer
* 5V Power Supply

---

## 💻 Software

* Language: Embedded C
* IDE: Keil µVision
* Programmer: 8051 Programmer

---

## 📂 Code

Main implementation is available in `main.c`

---

## 🚀 Future Improvements

* IoT-based monitoring (WiFi / Cloud)
* Mobile app integration
* Occupancy analytics dashboard

---

## 👨‍💻 Author

Harsh Maurya
