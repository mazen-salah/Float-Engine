# FloatEngine MATE Competition

## Overview

This repository contains the source code for the FloatEngine designed for participation in the MATE (Marine Advanced Technology Education) competition. The FloatEngine system is intended to control a motorized clock mechanism for underwater applications. It utilizes an Arduino microcontroller, a real-time clock (RTC) module, and an HC-12 wireless serial communication module.

## Components Used

- Arduino microcontroller
- RTC module (DS3231)
- HC-12 wireless serial module

## Dependencies

- **SoftwareSerial.h**: Library for serial communication on digital pins.
- **Wire.h**: Library for I2C communication.
- **RTClib.h**: Library for interfacing with the DS3231 RTC module.

## Pin Configuration

- `dirPin`: Pin connected to the direction control of the motor.
- `dirPin2`: Secondary pin for direction control.
- `lSwitch`: Pin connected to the limit switch for motor position detection.
- HC-12 module is connected to digital pins 8 (RX) and 9 (TX).

## Operation

1. **Initialization**: The system initializes all necessary components including pins, serial communication, and the RTC module. It sends the clock signal repeatedly for 15 seconds during the setup phase.
  
2. **Main Loop**:
   - The system continuously performs the profile operation and sends the current time over the HC12 module.

3. **Profile Operation**:
   - The motor moves down, transmitting a clock signal for 6 seconds.
   - It waits for the limit switch to be triggered, then stops the motor and waits for 30 seconds.
   - The motor then moves up, transmitting a clock signal again for 6 seconds.
   - It waits for the limit switch to be triggered once more, stops the motor, and waits for another 30 seconds.

4. **Transmission**:
   - The `transmit` function allows for the transmission of a clock signal for a specified duration.

5. **Motor Control**:
   - `up()`: Moves the motor up.
   - `down()`: Moves the motor down.
   - `rotate()`: Rotates the motor in the specified direction.
   - `stopMotor()`: Stops the motor.

6. **Clock Transmission**:
   - The `sendClock` function retrieves the current time from the RTC module and transmits it over the HC-12 module in the format "Orcas EX05 HH:MM:SS".

## Usage

1. Ensure all components are properly connected to the Arduino board.
2. Upload the provided code to the Arduino.
3. Power on the system.
4. Monitor the HC-12 module for clock signal transmissions.

## Notes

- Adjust `downDelay` and `upDelay` variables to customize the delay between motor movements.
- Modify the `transmit` function to change the duration of clock signal transmissions.
- Ensure proper wiring and setup of the limit switch for accurate motor position detection.

For any inquiries or assistance, please contact me.
