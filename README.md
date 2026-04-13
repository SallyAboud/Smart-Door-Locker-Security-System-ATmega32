# Smart-Door-Locker-Security-System-ATmega32
A secure embedded system project that implements a smart door locking mechanism using dual ATmega32 microcontrollers with password authentication.




## Overview
This project is based on two ECUs:
- HMI_ECU → handles user interaction (LCD & keypad)
- Control_ECU → handles system logic (motor, EEPROM, sensors)

The system allows users to set, verify, and change a password to control door access.



## Features
-  Password-based authentication
-  LCD + Keypad interface
-  UART communication between two MCUs
-  External EEPROM for password storage
-  Motorized door control using H-bridge
-  Buzzer alarm for security alerts
-  PIR motion sensor detection
-  System lock after 3 failed attempts


## Communication:
- UART (MCU ↔ MCU)
- I2C (EEPROM)



## Hardware Components
- ATmega32 (2 units)
- LCD (16x2)
- 4x4 Keypad
- External EEPROM
- PIR Sensor
- DC Motor + H-Bridge
- Buzzer



## How It Works
1. User sets a password
2. Password is stored in EEPROM
3. User chooses:
- Open Door
- Change Password
4. System verifies password
5. Door opens/closes using motor
6. Alarm triggers after 3 wrong attempts



## Drivers Used
- GPIO
- UART
- I2C (TWI)
- LCD
- Keypad
- Timer (Interrupt-based)
- PWM (Motor control)
- EEPROM
- PIR Sensor
- Buzzer



## Demo
[Proteus Simulation](https://drive.google.com/file/d/1OgTgJOjIU6jK3GR51RRVD_WEoPtjxL8e/view?usp=sharing)
