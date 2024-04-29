#include <SoftwareSerial.h>
#include <Wire.h>
#include <RTClib.h>

#define antiClockwise 0
#define clockwise 1
#define dirPin 6
#define dirPin2 7
#define lSwitch 10

RTC_DS3231 rtc;
SoftwareSerial HC12(9, 8);

const int downDelay = 30;
const int upDelay = 30;

unsigned long transmitStartTime;
unsigned long transmitDuration;


/**
 * @brief Initializes the necessary components and sets up the initial configuration.
 */
void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(lSwitch, INPUT);
  HC12.begin(9600);
  rtc.begin();
  for (int i = 0; i < 30; i++) {
    sendClock();
    delay(500);
  }
}

/**
 * @brief The main loop that runs continuously.
 */
void loop() {
  profile();
  sendClock();
}

/**
 * @brief Transmits clock signal for a specified duration.
 * 
 * @param duration The duration in milliseconds for which the clock signal should be transmitted.
 */
void transmit(unsigned long duration) {

  transmitDuration = duration;
  transmitStartTime = millis();
  while (millis() - transmitStartTime < transmitDuration) {
    sendClock();
    delay(150);
  }
}

/**
 * @brief Performs the profile operation.
 * 
 * The profile operation consists of moving the motor down, transmitting the clock signal for a specified duration,
 * waiting for the limit switch to be triggered, stopping the motor, waiting for a delay, moving the motor up,
 * transmitting the clock signal for a specified duration, waiting for the limit switch to be triggered again,
 * stopping the motor, and waiting for another delay.
 */
void profile() {
  down();
  transmit(6000);
  while (digitalRead(lSwitch) == HIGH) {
    sendClock();
  }
  stopMotor();
  transmit(downDelay * 1000);
  up();
  transmit(6000);
  while (digitalRead(lSwitch) == HIGH) {
    sendClock();
  }
  stopMotor();
  transmit(upDelay * 1000);
}

/**
 * @brief Moves the motor up.
 */
void up() {
  rotate(antiClockwise);
}

/**
 * @brief Moves the motor down.
 */
void down() {
  rotate(clockwise);
}

/**
 * @brief Rotates the motor in the specified direction.
 * 
 * @param direction The direction in which the motor should rotate. Use the constants `antiClockwise` or `clockwise`.
 */
void rotate(int direction) {
  digitalWrite(dirPin, direction);
  digitalWrite(dirPin2, !direction);
}

/**
 * @brief Stops the motor.
 */
void stopMotor() {
  digitalWrite(dirPin, LOW);
  digitalWrite(dirPin2, LOW);
}

/**
 * @brief Sends the current time over the HC12 module.
 */
void sendClock() {
  DateTime now = rtc.now();
  HC12.print("Orcas EX05 ");
  HC12.print(now.hour(), DEC);
  HC12.print(':');
  HC12.print(now.minute(), DEC);
  HC12.print(':');
  HC12.print(now.second(), DEC);
  HC12.println("");
}
