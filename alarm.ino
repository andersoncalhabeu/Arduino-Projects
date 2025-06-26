
/* Sensor_inclinacao Program for:

  - SW-520D tilt sensor module

  - passive buzzer

  modified by Anderson Muniz Calhabeu 

The SW-520D is a simple and cost-effective tilt sensor used to detect changes in orientation or inclination. Here's a breakdown of how it works and what it's typically used for:

Mechanical Design:
Inside the cylindrical sensor is a small conductive ball or metal contact that rolls or shifts when the sensor is tilted.

Electrical Behavior:
When the sensor is upright, the ball makes contact between two terminals, closing the circuit.
When tilted beyond a certain angle, the ball moves away, breaking the circuit.
It acts like a switch: either ON (closed) or OFF (open) depending on its orientation.

Typical Features
Digital Output:
It usually connects to a microcontroller (like Arduino) via a digital input pin.
Debouncing Needed:
Because it's mechanical, it can produce noisy signals when the ball bounces—software debouncing or filtering is often used.
Low Power:
Very low current draw, ideal for battery-powered projects.


*/


int buzzer = 8;                                              // Defines a global variable of type "int" called "buzzer" and assigns it the value 8

const int entra_sensor_tilt = 2;

void setup() {

  pinMode(buzzer, OUTPUT);                                   // Sets the buzzer pin, i.e., Arduino pin 8, as an output (OUTPUT)

  pinMode(LED_BUILTIN, OUTPUT);                              // Sets the LED_BUILTIN pin, i.e., Arduino pin 13, as an output (OUTPUT)

  pinMode(entra_sensor_tilt, INPUT);                         // Sets Arduino pin 2 as an input (INPUT)

}

void loop() {

  unsigned char i, j;                                        // Declares two local variables of type "unsigned char" named "i" and "j"

  int ValorDig = digitalRead(entra_sensor_tilt);             // Declares a local variable of type "int" called "ValorDig" and assigns it the value read from pin 2 - Syntax: digitalRead(pin)

  if (HIGH == ValorDig) {                                    // If the value of "ValorDig" is equal to 5V (HIGH)...

    digitalWrite(LED_BUILTIN, LOW);                          // then set the LED pin to 0V (LOW), turning the LED off

  } else {                                                   // otherwise, if the value of "ValorDig" is equal to 0V (LOW)...

    digitalWrite(LED_BUILTIN, HIGH);                         // turn the LED on

    /////////////////////////////////////////////////// Creates sound for the buzzer ///////////////////////////////////////////////////

    //////////////////////////////////////////////////// Produces a frequency /////////////////////////////////////////////////////////

    for (i = 0; i < 80; i++) {                               // For i from 0 to 80, incrementing by 1...

      digitalWrite(buzzer, HIGH);                            // Sets the buzzer pin (pin 8) to 5V (HIGH)
      delay(1);                                              // Pauses the program for 1 millisecond - Syntax: delay(milliseconds)
      digitalWrite(buzzer, LOW);                             // Sets the buzzer pin (pin 8) to 0V (LOW)
      delay(1);                                              // Pauses the program for 1 millisecond
    }

    ////////////////////////////////////////////// Produces a second frequency ////////////////////////////////////////////////////////

    for (j = 0; j < 100; j++) {                              // For j from 0 to 100, incrementing by 1...

      digitalWrite(buzzer, HIGH);                            // Sets the buzzer pin (pin 8) to 5V (HIGH)
      delay(2);                                              // Pauses the program for 2 milliseconds
      digitalWrite(buzzer, LOW);                             // Sets the buzzer pin (pin 8) to 0V (LOW)
      delay(2);                                              // Pauses the program for 2 milliseconds
    }
  }
}
