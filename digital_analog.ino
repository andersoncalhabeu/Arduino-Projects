/*
  Program: digital_analog

  Developed by Miguel F. R. Calhabeu and Anderson Calhabeu
*/

////////////////////////////////////////// Constant Definitions //////////////////////////////////////////////////////////////

const int led_analog = 9;                      // Defines a constant of type "int" called "led_analog"

const int button = 2;                          // Defines a constant of type "int" called "button"

const int led_digital = 3;                     // Defines a constant of type "int" called "led_digital"

////////////////////////////////////////// Variable Definitions //////////////////////////////////////////////////////////////

int analog_input;                              // Defines a global variable of type "int" called "analog_input"

bool digital_output;                           // Defines a global variable of type "bool" called "digital_output"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {

  pinMode(led_analog, OUTPUT);                 // Sets the "led_analog" pin as output - Used for the analog LED - Since "led_analog" is 9, sets pin 9 as output
  pinMode(button, INPUT_PULLUP);               // Sets the "button" pin as input with internal pull-up resistor - Used for button reading - Since "button" is 2, sets pin 2 as input
  pinMode(led_digital, OUTPUT);                // Sets the "led_digital" pin as output - Used for the digital LED - Since "led_digital" is 3, sets pin 3 as output
  Serial.begin(9600);                          // Starts serial communication at 9600 bps. Syntax: Serial.begin(speed)

}

void loop() {

  ///////////////////////////////////////// Analog Inputs and Outputs /////////////////////////////////////////////////////////

  analog_input = analogRead(A2);               // Reads the analog input from pin A2 and stores the value in "analog_input"
  Serial.print("Before 'map' command - ");     // Sends the message "Before 'map' command" to the serial monitor
  Serial.print(analog_input);                  // Sends the value of "analog_input" to the serial monitor
  analog_input = map(analog_input, 0, 1023, 0 , 255); // Maps a number from one range to another. Syntax: map(value, fromLow, fromHigh, toLow, toHigh)
  Serial.print(" - After 'map' command - ");   // Sends the message "After 'map' command" to the serial monitor
  Serial.print(analog_input);                  // Sends the mapped value of "analog_input" to the serial monitor
  analogWrite(led_analog, analog_input);       // Sends the value of "analog_input" to the "led_analog" pin. Syntax: analogWrite(pin, value)

  //////////////////////////////////////// Digital Inputs and Outputs /////////////////////////////////////////////////////////

  Serial.print(" - digital output: ");         // Sends the message " - digital output: " to the serial monitor
  digital_output = digitalRead(button);        // Reads the digital input from "button" and stores the value in "digital_output"
  Serial.println(digital_output);              // Sends the value of "digital_output" to the serial monitor and moves to the next line
  digitalWrite(led_digital, digital_output);   // Sends the value of "digital_output" to the "led_digital" pin. Syntax: digitalWrite(pin, value)

  /*                         Alternative commands to the two lines above. These allow skipping the "digital_output" variable
    Serial.println(led_digital);               // Directly sends the value of the expression " - digital output: " to the serial monitor
    digitalWrite(led_digital, digitalRead(button)); // Directly sends the value of the "button" input to the "led_digital" pin. Syntax: digitalWrite(pin, value)
  */

  delay(100);                                  // Pauses the program for 100 milliseconds. Syntax: delay(milliseconds)

}
