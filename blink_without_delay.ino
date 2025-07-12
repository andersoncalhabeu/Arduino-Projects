/*
  Program: blink_without_delay

  Turns an LED on and off connected to a digital pin, without using the delay() function.
  This means other code can run at the same time without being interrupted by "delay".

  Created in 2005 by David A. Mellis
  Modified on February 8, 2010 by Paul Stoffregen
  Modified on November 11, 2013 by Scott Fitzgerald
  Modified on January 9, 2017 by Arturo Guadalupi
  Modified on May 16, 2020 by Anderson Calhabeu

  This example is public domain and can be found at:

  http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
*/

///////////////////////////////////////////// Constant and variable definitions /////////////////////////////////////////////

const int ledPin = LED_BUILTIN;                  // Defines a constant of type "int" named "ledPin" and assigns it the predefined value "LED_BUILTIN" (usually pin 13)

const long interval = 1000;                      // Defines a constant of type "long" named "interval" and assigns it the value 1000 (milliseconds between blinks)

int ledState = LOW;                              // Defines a global variable of type "int" named "ledState" and sets it to "LOW" – indicates the LED state

unsigned long previousMillis = 0;                /* Defines a global variable of type "unsigned long" and sets it to zero.
                                                    It stores the last time the LED was updated.
                                                    You should use "unsigned long" for timekeeping variables,
                                                    as the value can quickly exceed the limit of an "int".
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  pinMode(ledPin, OUTPUT);                       // Sets the ledPin as an output – since ledPin equals LED_BUILTIN (usually 13), sets pin 13 as output
}

void loop() {

  unsigned long currentMillis = millis();        // Defines a local variable "currentMillis" and assigns it the current time in milliseconds

  if (currentMillis - previousMillis >= interval) {  // If the time since the last LED update is greater than or equal to the interval...
    previousMillis = currentMillis;              // Save the last time the LED was toggled

    if (ledState == LOW) {                       // If the LED is off...
      ledState = HIGH;                           // Turn the LED on
    } else {                                     // Otherwise, if the LED is on...
      ledState = LOW;                            // Turn the LED off
    }

    // Full syntax for "if...else" can be found at: https://www.arduino.cc/reference/en/language/structure/control-structure/else/

    digitalWrite(ledPin, ledState);              // Sends the value of "ledState" to the pin "ledPin"
  }
}
