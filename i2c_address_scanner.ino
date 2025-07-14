/* I2C Address Scanner Program

   Purpose: Determine the addresses of I2C devices connected to the Arduino using 7-bit standard addresses

   Original author unknown

   Adapted by users Krodal and louarnold

   Modified by Anderson Muniz Calhabeu */

#include <Wire.h>  // Includes the "Wire" library for I2C communication

void setup()
{
  Wire.begin();  // Initializes the "Wire" library

  Serial.begin(9600);  // Starts the serial monitor at 9600 bps
  while (!Serial);     // Waits for the serial monitor - added for Arduino Leonardo
  Serial.println("\nI2C Address Scanner");  // Prints "I2C Address Scanner" to the serial monitor
}

void loop()
{
  byte error, address;  // Local variables of type "byte" named "error" and "address"
  int nDevices;         // Local variable of type "int" named "nDevices"

  Serial.println("Scanning...");  // Prints "Scanning..." to the serial monitor

  nDevices = 0;  // Initializes "nDevices" to 0
  for (address = 1; address < 127; address++ ) {  // Scans addresses from 1 to 126
    Wire.beginTransmission(address);  // Attempts to start transmission with an I2C device at "address"
    error = Wire.endTransmission();   // Checks if communication was successful

    if (error == 0) {  // If no error occurred
      Serial.print("I2C device found at address 0x");  // Prints message to serial monitor
      if (address < 16)
        Serial.print("0");  // Adds leading zero for addresses less than 0x10
      Serial.print(address, HEX);  // Prints the address in hexadecimal
      Serial.println("  !");
      nDevices++;  // Increments the device count
    }
    else if (error == 4) {  // If an unknown error occurred
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("Done\n");

  delay(2000);  // Waits for 2 seconds before scanning again
}
