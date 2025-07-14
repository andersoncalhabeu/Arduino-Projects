/*
  Program: scale_v1 for:

  - Load cell;
  - HX711 converter module

  Developed by Anderson Muniz Calhabeu based on a program by Bogdan Necula
*/

#include "HX711.h"  // Include the HX711 module library

///////////////////////////////////////////// Define pin numbers for HX711 module ///////////////////////////////////////////////////////////

const int Pin_DT_HX711 = 3;  // Define pin 3 as the DT pin of the HX711 module
const int Pin_SCK_HX711 = 2; // Define pin 2 as the SCK pin of the HX711 module

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HX711 scale;  // Create an object called 'scale'

void setup() {

  Serial.begin(38400);  // Start serial communication at 38400 bps

  Serial.println("Initializing the scale");  // Send the message to the serial monitor

  scale.begin(Pin_DT_HX711, Pin_SCK_HX711);  // Initialize the HX711 module

  /////////////////////////////////////////////////// Scale calibration //////////////////////////////////////////////////////////////////////////

  Serial.println("Before calibrating the scale:");
  Serial.print("Reading:			");
  Serial.println(scale.read());  // Send a raw reading from the HX711 module

  Serial.print("Average reading:			");
  Serial.println(scale.read_average(20));  // Send the average of 20 raw readings

  Serial.print("Get value:			");
  Serial.println(scale.get_value(5));  // Send the average of 5 raw readings minus the tare value

  Serial.print("Get units:		");
  Serial.println(scale.get_units(5), 1);  // Send the average of 5 readings divided by the scale factor

  scale.set_scale(431.f);  // Calibrate the scale factor obtained from known mass values

  scale.tare();  // Tare the scale

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  Serial.println("After calibrating the scale:");
  Serial.println("Readings:");
}

void loop() {
  Serial.print("Single reading:	");
  Serial.print(scale.get_units(), 1);  // Send a single mass reading
  Serial.print("	| Average:	");
  Serial.println(scale.get_units(5), 1);  // Send the average of 5 mass readings
  scale.power_down();  // Put the HX711 module in sleep mode
  delay(1);  // Pause for 1 millisecond
  scale.power_up();  // Wake up the HX711 module
}
