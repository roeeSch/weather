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

// 2-wire basic config, microstepping is hardwired on the driver
//BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

const int selectPin =5;//Low = mot #0, Hight = mot #3

//Uncomment line to use enable/disable functionality
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, ENABLE);

void setup() {
    pinMode(selectPin, OUTPUT);
    digitalWrite(selectPin, LOW);

    stepper.begin(RPM, MICROSTEPS);
    stepper.disable();
}

void loop() {
  
    // energize coils - the motor will hold position
    delay(2000);
    
  
    /*
     * Moving motor one full revolution using the degree notation
     */
    stepper.enable();
    stepper.rotate(-360*30);
    stepper.disable();

    delay(1000);
    /*
     * Moving motor to original position using steps
     */
    stepper.enable();
    stepper.move(MOTOR_STEPS*MICROSTEPS*30);
    stepper.disable();

    // pause and allow the motor to be moved by hand
    // stepper.disable();

    delay(2000);

    digitalWrite(selectPin, HIGH);

    /*
     * Moving motor one full revolution using the degree notation
     */
    stepper.enable();
    stepper.rotate(-360*30);
    stepper.disable();

    delay(1000);
    /*
     * Moving motor to original position using steps
     */
    stepper.enable();
    stepper.move(MOTOR_STEPS*MICROSTEPS*30);
    // pause and allow the motor to be moved by hand
    stepper.disable();

    delay(10);

    digitalWrite(selectPin, LOW);
}


/*
// The selectMuxPin function sets the S0, S1, and S2 pins
// accordingly, given a pin from 0-7.
void selectMuxPin(byte pin)
{
  if (pin > 7) return; // Exit if pin is out of scope
  for (int i=0; i<3; i++)
  {
    if (pin & (1<<i))
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }
}
*/
