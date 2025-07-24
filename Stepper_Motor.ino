/*
  Stepper_Motor Program for unipolar stepper motor 28BYJ-48 with ULN2003 driver module

  Adapted by Anderson Muniz Calhabeu based on a program from DroneBot Workshop

       ////////////////////////////  Stepper Motor Driver Wiring Diagram  ////////////////////////////
                                           Pin 8 to IN1 of ULN2003 driver
                                           Pin 9 to IN2 of ULN2003 driver
                                           Pin 10 to IN3 of ULN2003 driver
                                           Pin 11 to IN4 of ULN2003 driver

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

#include <Stepper.h>                                               // Includes the Arduino Stepper library

///////////////////////////////////// Constant Definitions ///////////////////////////////////////////////

const int steps_per_revolution = 32;                               // Number of steps per revolution of the internal motor - according to 28BYJ-48 specs

const int gear_reduction = 64;                                     // Gear reduction factor - according to 28BYJ-48 specs

const int output_shaft_steps = steps_per_revolution * gear_reduction; // Number of steps per revolution of the external shaft. In this case, 32x64 = 2048 steps per full revolution

///////////////////////////////////// Variable Definitions ///////////////////////////////////////////////

int required_steps;                                                // Defines a global variable of type "int" to move the motor a number of steps and control the rotation direction

///////////////////////////////////////////////////////////////////////////////////////////////////////////

Stepper stepperMotor(steps_per_revolution, 8, 10, 9, 11);          // Creates the object 'stepperMotor'. Pay attention to the pin order

void setup()
{
  // Nothing needed here. However, both Setup and Loop functions must be present in any Sketch
}

void loop()
{
  ////////////////////////////// Slow sequencing of the ULN2003 driver board LEDs with four steps //////////////////////////////

  stepperMotor.setSpeed(1);                                        // Sets the internal motor speed to 1 rpm - Due to gear reduction, the external shaft rotates 1/64 times slower
  required_steps = 4;                                              // Defines the number of steps to be executed
  stepperMotor.step(required_steps);                               // Moves the stepper motor by the defined number of steps
  delay(1000);                                                     // Pauses the program for 1000 milliseconds (1 second)

  //////////////////////////////////// Slowly rotates the shaft clockwise by half a turn /////////////////////////////////////

  required_steps = output_shaft_steps / 2;                         // Defines the number of steps to be executed. Since "output_shaft_steps" is for a full turn, dividing by 2 gives half a turn
  stepperMotor.setSpeed(100);                                      // Sets the internal motor speed to 100 rpm - External shaft rotates at ~1.5 rpm
  stepperMotor.step(required_steps);                               // Moves the stepper motor by the defined number of steps
  delay(1000);                                                     // Pauses the program for 1000 milliseconds (1 second)

  ///////////////////////////////// Quickly rotates the shaft counterclockwise by one full turn //////////////////////////////////

  required_steps = -output_shaft_steps;                            // Defines the number of steps to be executed (negative for counterclockwise)
  stepperMotor.setSpeed(10 * gear_reduction);                      // Sets internal motor speed to 640 rpm - External shaft rotates at 10 rpm
  stepperMotor.step(required_steps);                               // Moves the stepper motor by the defined number of steps
  delay(1000);                                                     // Pauses the program for 1000 milliseconds (1 second)
}
