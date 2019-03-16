/*
 * Simple demo, should work with any driver board
 *
 * Connect STEP, DIR as indicated
 *
 * Copyright (C)2015-2017 Laurentiu Badea
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#include <Arduino.h>
#include "BasicStepperDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 20
#define RPM 240//960

// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
#define MICROSTEPS 16

// All the wires needed for full functionality
#define DIR 8
#define STEP 9
//Uncomment line to use enable/disable functionality
#define ENABLE 6


//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 10;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 12;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 11;

// 2-wire basic config, microstepping is hardwired on the driver
//BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

const int selectPin =5;//Low = mot #0, Hight = mot #3

//Uncomment line to use enable/disable functionality
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, ENABLE);

void setup() {
    pinMode(selectPin, OUTPUT);
    digitalWrite(selectPin, LOW);

    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);  
    pinMode(clockPin, OUTPUT);

    stepper.begin(RPM, MICROSTEPS);
    stepper.disable();

    Serial.begin(9600);
    Serial.println("reset");
}

void loop() {
  
    // energize coils - the motor will hold position
    delay(2000);
    
  
    /*
     * Moving motor one full revolution using the degree notation
     */
    // Select motor #1
    delay(10);
    registerWrite(1, HIGH);
    delay(10); 
    stepper.enable();
    stepper.rotate(-360*30);
    stepper.disable();
    delay(10);
    // unselect motor 1:
    registerWrite(1, LOW);
    delay(10);


    // Select motor #2
    delay(10);
    registerWrite(2, HIGH);
    delay(10); 
    stepper.enable();
    stepper.rotate(-360*30);
    stepper.disable();
    delay(10);
    // unselect motor 2:
    registerWrite(2, LOW);
    delay(10);


    // Select motor #3
    delay(10);
    registerWrite(3, HIGH);
    delay(10); 
    stepper.enable();
    stepper.rotate(-360*30);
    stepper.disable();
    delay(10);
    // unselect motor 3:
    registerWrite(3, LOW);
    delay(10);



}


// This method sends bits to the shift register:
void registerWrite(int whichPin, int whichState) {
// the bits you want to send
  byte bitsToSend = 0;

  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latchPin, LOW);

  // turn on the next highest bit in bitsToSend:
  bitWrite(bitsToSend, whichPin, whichState);

  // shift the bits out:
  shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);

    // turn on the output so the LEDs can light up:
  digitalWrite(latchPin, HIGH);

}
