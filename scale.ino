/*
  Program scale_v1 for:

  - Load cell;
  - HX711 ADC module;
  - I2C LCD module

  Developed by Anderson Muniz Calhabeu based on a program by Bogdan Necula
*/

#include "HX711.h"                            // Includes the "HX711" library for the ADC module

#include <Wire.h>                             // Includes the "Wire" library for I2C communication

#include <LiquidCrystal_I2C.h>                // Includes the "LiquidCrystal_I2C" library for the I2C LCD

/////////////////////////////////////// Define pin numbers for HX711 module /////////////////////////////////////////

const int Pino_DT_HX711 = 2;                  // Defines pin 2 as the DT pin of the HX711 module

const int Pino_SCK_HX711 = 3;                 // Defines pin 3 as the SCK pin of the HX711 module

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LiquidCrystal_I2C lcd(0x27, 16, 2);           // Sets address 0x27 for a 16x2 LCD (16 characters, 2 lines)

HX711 scale;                                  // Creates an object named 'scale'

void setup() {

  Serial.begin(38400);                        // Starts serial communication at 38400 bps

  Serial.println("Initializing scale");       // Sends "Initializing scale" to the serial monitor

  scale.begin(Pino_DT_HX711, Pino_SCK_HX711); // Initializes the HX711 module

  ///////////////////////////////////////////// Scale calibration ///////////////////////////////////////////////////

  Serial.println("Before calibrating the scale:");

  Serial.print("Reading:\t\t\t");             // "\t" adds tab spacing
  Serial.println(scale.read());               // Sends a raw reading from HX711 to the serial monitor

  Serial.print("Average reading:\t\t\t");
  Serial.println(scale.read_average(20));     // Sends the average of 20 raw readings

  Serial.print("Get value:\t\t\t");
  Serial.println(scale.get_value(5));         // Sends the average of 5 raw readings minus the tare

  Serial.print("Get units:\t\t");
  Serial.println(scale.get_units(5), 1);      // Sends the average of 5 readings divided by scale factor

  scale.set_scale(431.f);                     // Sets the scale factor based on known weights

  scale.tare();                               // Tares the scale (sets current weight as zero)

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  Serial.println("After calibrating the scale:");
  Serial.println("Readings:");

  lcd.init();                                 // Initializes the LCD
  lcd.backlight();                            // Turns on LCD backlight
  lcd.setCursor(1, 0);                        // Sets cursor to column 1, row 0
  lcd.print("Initializing");                  // Displays "Initializing" on LCD
  lcd.setCursor(1, 1);                        // Sets cursor to column 1, row 1
  lcd.print("v 1.1");                         // Displays "v 1.1" on LCD
  delay(1000);                                // Waits for 1 second
}

void loop() {
  Serial.print("One reading:\t");
  Serial.print(scale.get_units(), 1);         // Sends one weight reading to serial monitor
  Serial.print("\t| Average:\t");
  Serial.println(scale.get_units(5), 1);      // Sends average of 5 readings

  lcd.clear();
  lcd.setCursor(1, 0);                         // Sets cursor to column 1, row 0
  lcd.print("Mass");                           // Displays "Mass" on LCD
  lcd.setCursor(1, 1);                         // Sets cursor to column 1, row 1
  lcd.print(scale.get_units(5), 0);            // Displays weight value
  lcd.print(" g");                             // Displays "g" for grams
}
