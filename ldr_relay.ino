/*
  LDR Program for:

  - LDR (Light Dependent Resistor)
  - 5V Relay Module

  Developed by Anderson Muniz Calhabeu
*/

#define digital_input 2                                     // Defines a constant named "digital_input" and assigns it the value 2

#define digital_output 4                                    // Defines a constant named "digital_output" and assigns it the value 4

void setup() {

  pinMode(digital_input, INPUT);                            // Sets the "digital_input" pin as input - Used for the digital output of the LDR module

  pinMode(digital_output, OUTPUT);                          // Sets the "digital_output" pin as output - Used to control the relay

  Serial.begin(9600);                                       // Starts serial communication at 9600 bps

}

void loop() {

  Serial.print("Analog value: ");                           // Sends the message "Analog value: " to the serial monitor
  Serial.print(analogRead(A2));                             // Sends the value read from analog pin A2 to the serial monitor
  Serial.print(" - Digital value: ");                       // Sends the message " - Digital value: " to the serial monitor
  Serial.println(digitalRead(digital_input));               // Sends the digital value read from the LDR module to the serial monitor

  if (digitalRead(digital_input) == 1) {                    // If "digital_input" is equal to 1...
    digitalWrite(digital_output, LOW);                      // Sets "digital_output" to LOW and activates the relay
  }
  else {                                                    // Otherwise...
    digitalWrite(digital_output, HIGH);                     // Sets "digital_output" to HIGH and deactivates the relay
  }

  delay(100);                                               // Pauses the program for 100 milliseconds
}
