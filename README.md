# Stamping Machine Project - Arduino

## Project Overview
This project implements an Arduino-based stamping machine controller. The machine handles operations such as paper positioning, stamping, and feeding. Communication between multiple Arduino boards is facilitated using the Wire library, while an LCD display provides real-time status updates.

The code controls three motors (M1, M2, M3) that handle the paper feed and stamping process, and sends commands to two other motors (M4, M5) via I2C communication for stamping and stage movement. Several sensors and buttons monitor the state of the machine, allowing the operator to control operations and detect issues such as empty paper stacks.

## Features
- **Motor control**: Drives three motors to handle paper feeding and movement.
- **Inter-Arduino Communication**: Sends commands to additional motors using the I2C protocol.
- **LCD Display**: Provides feedback on the machine's current state.
- **State Management**: Manages different states such as WORKING, SETTING, PAPEREMPTY, and PAPERFILL.
- **Safety Mechanisms**: Monitors paper levels and ensures correct operation through switches and buttons.

## Components Used
- **Arduino Uno**: Main controller board.
- **LiquidCrystal_I2C Display**: 16x2 LCD display for status updates.
- **DC Motors (M1, M2, M3)**: Control paper movement and feed.
- **Sensors/Buttons**: Detect machine states, such as on/off, paper empty, and paper fully positioned.
- **Wire Library**: For communication between two Arduino boards.

## Pins Configuration
- **M1 Motor**: Pin 3, 4, 5.
- **M2 Motor**: Pin 7, 8, 9.
- **M3 Motor**: Pin 10, 11, 12.
- **Input Switches**: A0 (on/off), A1 (paper full), A2 (max feeder down), A3 (paper empty).

## How It Works
1. **Setup**: Initializes motors, buttons, and the LCD display.
2. **Loop**: Continuously checks machine status based on inputs and controls motor actions accordingly.
3. **Communication**: Sends and receives messages via I2C to manage additional motors (M4 and M5).
4. **State Machine**: Transitions between different states (WORKING, SETTING, PAPEREMPTY, PAPERFILL) based on sensor feedback and user input.

## Usage
1. **Start the Machine**: Use the on/off button (A0) to power on the machine.
2. **Automatic Control**: The machine will automatically handle paper feed and stamping based on motor control and switch feedback.
3. **State Transition**: The machine automatically transitions between states like WORKING and PAPEREMPTY as conditions change (e.g., paper runs out).

