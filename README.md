# Automotive CAN-Based Vehicle Dashboard

## Project Overview

The Automotive CAN-Based Vehicle Dashboard is an embedded system project developed using multiple PIC18F4580 ECUs to monitor and display vehicle parameters such as speed, RPM, gear position, and indicator status.

The project uses the Controller Area Network (CAN) protocol to exchange sensor and control information between multiple ECUs. The dashboard ECU receives the transmitted information and displays the corresponding vehicle parameters on an LCD.

## Features

- Speed monitoring
- RPM monitoring
- Gear position monitoring
- Indicator status monitoring
- CAN-based communication between multiple ECUs
- ADC-based speed and RPM measurement
- Real-time display of vehicle parameters
- UART-based debugging

## Hardware Used

- PIC18F4580 Microcontroller
- CAN Transceiver
- 16x2 LCD
- Potentiometer for ADC-based inputs
- LEDs for indicator status
- UART interface

## Software and Technologies

- Embedded C
- PIC18F4580
- CAN Protocol
- ADC
- UART
- LCD Interfacing
- Timers
- Interrupts
- MPLAB X IDE
- XC8 Compiler

## System Architecture

The project consists of three ECUs communicating through the CAN bus.

### ECU 1

ECU 1 is responsible for acquiring and processing the vehicle speed.

- Reads speed input using ADC.
- Converts the ADC reading into the corresponding speed value.
- Transmits the speed information through CAN.

### ECU 2

ECU 2 is responsible for acquiring and processing engine RPM and indicator-related information.

- Reads RPM input using ADC.
- Converts the ADC reading into the corresponding RPM value.
- Processes indicator information.
- Transmits the required information through CAN.

### ECU 3 – Dashboard

ECU 3 acts as the vehicle dashboard.

- Receives vehicle parameters through CAN.
- Processes the received CAN messages.
- Displays vehicle parameters on the LCD.
- Displays information such as speed, RPM and gear position.
- Handles indicator status.

## CAN Communication

The ECUs communicate with each other using the Controller Area Network (CAN) protocol.

Each CAN message is identified using a message ID, allowing the receiving ECU to determine the type of information being transmitted.

The project demonstrates multi-ECU communication over a common CAN bus and real-time exchange of vehicle parameters.

## ADC-Based Parameter Measurement

ADC inputs are used to obtain speed and RPM values.

The ADC readings are processed and converted into corresponding vehicle parameter values before being transmitted through the CAN bus.

## Key Challenges & Learnings

- Implemented communication between multiple ECUs using the CAN protocol to transmit and receive vehicle parameters.
- Interfaced ADC inputs to measure speed and RPM and converted the corresponding ADC values into vehicle parameter readings.
- Implemented timer interrupts and indicator control while ensuring that the main application remained responsive.
- Faced challenges while debugging CAN message transmission/reception, ADC readings and real-time data updates.
- Gained practical understanding of embedded C programming, microcontroller peripherals, CAN communication and real-time embedded system development.

## Project Structure

```text
CAN_Dashboard/
│
├── ECU1.X/
│   └── ECU 1 MPLAB X Project
│
├── ECU2.X/
│   └── ECU 2 MPLAB X Project
│
└── ECU3.X/
    └── ECU 3 MPLAB X Project
