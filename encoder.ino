/*
  Encoder Program for Incremental Rotary Encoder 600 Pulses NPN;

  Developed by Anderson Muniz Calhabeu
*/

/////////////////////////////////// Constant and Variable Definitions ///////////////////////////////////////////////

const float period = 200;                                                      // Defines and initializes with value 200 a constant of type "float" for the measurement cycle time
const byte interruptPin2 = 2;                                                  // Defines and initializes with value 2 a constant of type "byte" for one of the encoder signal pins
const byte interruptPin3 = 3;                                                  // Defines and initializes with value 3 a constant of type "byte" for the other encoder signal pin

volatile unsigned long temp = 0;                                               // Defines and initializes with zero a global variable of type "volatile unsigned long" for temporary storage of pulse count
volatile unsigned long time = 0;                                               // Defines and initializes with zero a global variable of type "volatile unsigned long" for measurement timing
volatile unsigned int counter = 0;                                             // Defines and initializes with zero a global variable of type "volatile unsigned int" for encoder pulse counting

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {

  Serial.begin(9600);                                                          // Starts serial communication at 9600 bps

  pinMode(interruptPin2, INPUT_PULLUP);                                        // Sets interruptPin2 (pin 2) as input with internal pull-up resistor
  pinMode(interruptPin3, INPUT_PULLUP);                                        // Sets interruptPin3 (pin 3) as input with internal pull-up resistor

  attachInterrupt(digitalPinToInterrupt(interruptPin2), ai0, CHANGE);          // Attaches interrupt to pin 2 on any change
  attachInterrupt(digitalPinToInterrupt(interruptPin3), ai1, CHANGE);          // Attaches interrupt to pin 3 on any change

}

void loop() {

  if (counter != temp) {                                                       // If the counter value has changed, i.e., the encoder is rotating
    if ((millis()) > (time + period)) {                                        // Waits for the defined period before reading the pulse count
      Serial.print(millis());                                                  // Sends the current time in milliseconds to the serial monitor
      Serial.print(";");                                                       // Sends a semicolon to the serial monitor
      Serial.println(counter);                                                 // Sends the pulse count to the serial monitor
      time = millis();                                                         // Updates the time variable with the current time
    }
    temp = counter;                                                            // Updates the temporary variable with the current counter value
  }
}

void ai0() {                                                                   // Triggered when interruptPin2 changes; checks pin 3 to determine direction
  if (digitalRead(interruptPin3) == LOW) {
    counter++;                                                                 // Increments the counter
  } else {
    counter--;                                                                 // Decrements the counter
  }
}

void ai1() {                                                                   // Triggered when interruptPin3 changes; checks pin 2 to determine direction
  if (digitalRead(interruptPin2) == LOW) {
    counter--;                                                                 // Decrements the counter
  } else {
    counter++;                                                                 // Increments the counter
  }
}

/*
   Note:
   Inside the ISR function, delay() won't work and millis() won't increment.
   Serial data received during ISR execution may be lost.
   You must declare as volatile any variables modified inside the ISR.
   See the section on ISRs for more information.

   Source: https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
*/
