/*
  BMP180 Program for temperature and pressure sensor module.

  Developed by Anderson Muniz Calhabeu
*/

#include <SFE_BMP180.h>                          // Includes the BMP180 module library

#include <Wire.h>                                // Includes the Wire library for I2C communication

SFE_BMP180 bmpModule;                            // Creates an object named 'bmpModule'

#define ALTITUDE 759.0                           // Defines a constant named "ALTITUDE" and assigns it the local altitude in meters

void setup() {

  Serial.begin(9600);                            // Starts serial communication at 9600 bps
  Serial.println("Restarting");                  // Sends "Restarting" to the serial monitor

  if (bmpModule.begin())                         // Initializes the module. If successful...
    Serial.println("BMP180 module successfully initialized");
  else {
    Serial.println("Failed to initialize BMP180\n\n");  // Sends error message and breaks the loop
    while (1);                                   // Infinite loop to halt further execution
  }
}

void loop() {

  char status;                                   // Declares a local variable of type "char" named "status"
  double T, P, p0, a;                            // Declares local variables for temperature, pressure, sea-level pressure, and calculated altitude

  Serial.println();                              // Adds a blank line in the serial monitor

  Serial.print("Provided local altitude: ");
  Serial.print(ALTITUDE, 0);
  Serial.println(" m\n");

  status = bmpModule.startTemperature();         // Attempts to start temperature reading

  if (status != 0) {

    delay(status);                               // Waits for the reading to complete

    status = bmpModule.getTemperature(T);        // Gets the temperature value and stores it in T

    if (status != 0) {

      Serial.print("Temperature: ");
      Serial.print(T, 0);
      Serial.println(" °C");

      status = bmpModule.startPressure(3);       // Starts pressure reading with oversampling setting 3

      if (status != 0) {

        delay(status);                           // Waits for the reading to complete

        status = bmpModule.getPressure(P, T);    // Gets pressure value using previously read temperature

        if (status != 0) {

          Serial.print("Absolute pressure: ");
          Serial.print(P, 2);
          Serial.print(" mBar , ");
          Serial.print(P * 0.75, 2);             // Converts mBar to mmHg
          Serial.println(" mmHg");

          p0 = bmpModule.sealevel(P, ALTITUDE);  // Calculates sea-level pressure
          Serial.print("Sea-level pressure: ");
          Serial.print(p0, 2);
          Serial.print(" mBar , ");
          Serial.print(p0 * 0.75, 2);            // Converts mBar to mmHg
          Serial.println(" mmHg");

          a = bmpModule.altitude(P, p0);         // Calculates altitude based on pressure
          Serial.print("Calculated altitude: ");
          Serial.print(a, 0);
          Serial.println(" m");

        } else Serial.println("Error reading pressure\n");
      } else Serial.println("Error starting pressure reading\n");
    } else Serial.println("Error reading temperature\n");
  } else Serial.println("Error starting temperature reading\n");

  delay(5000);                                   // Waits 5 seconds before next reading
}
