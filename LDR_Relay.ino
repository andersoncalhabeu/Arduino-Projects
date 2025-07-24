/*
  LDR Program for:

  - LDR (Light Dependent Resistor)
  - 5V Relay Module

  developed by Anderson Muniz Calhabeu
*/

#define digital_input 2                                       /* Defines a constant called "digital_input" and assigns it the value 2 - Syntax: #define constantName value
                                                                 Note that the line above is equivalent to: const int digital_input = 2, but uses less memory */

#define digital_output 4                                      // Defines a constant called "digital_output" and assigns it the value 4

void setup() {

  pinMode(digital_input, INPUT);                              // Sets the "digital_input" pin as input - Used for the digital output of the LDR module LED indicator - Syntax: pinMode(pin, mode)

  pinMode(digital_output, OUTPUT);                            // Sets the "digital_output" pin as output - Used to trigger the relay

  Serial.begin(9600);                                         // Starts serial communication at a baud rate of 9600 bps. Syntax: Serial.begin(speed)

}

void loop()

{

  Serial.print("Analog value: ");                             // Sends the text "Analog value: " to the serial monitor - Syntax: Serial.println(value) or Serial.println(value, format)
  Serial.print(analogRead(A2));                               // Sends the value from analog input A2 directly to the serial monitor - Syntax: analogRead(pin)
  Serial.print(" - Digital value: ");                         // Sends the text " - Digital value: " to the serial monitor
  Serial.println(digitalRead(digital_input));                 // Sends the value from digital input to the serial monitor and moves to a new line - Syntax: digitalRead(pin)
  if (digitalRead(digital_input) == 1) {                      // If "digital_input" equals 1... - Syntax: if (condition) {commands}
    digitalWrite(digital_output, LOW);                        // Sets "digital_output" to "LOW" and activates the relay - Syntax: digitalWrite(pin, value)
  }
  else {                                                      // Otherwise... - Syntax: else {commands}
    digitalWrite(digital_output, HIGH);                       // Sets "digital_output" to "HIGH" and deactivates the relay
  }

  delay(100);                                                 // Pauses the program for 100 milliseconds - Syntax: delay(milliseconds)
}
