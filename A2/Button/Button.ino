/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground through 220 ohm resistor
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button
*/

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 13;  // the number of the pushbutton pin
const int ledPin9 = 9;    // the number of the LED pin
const int ledPin10 = 10;    // the number of the LED pin
const int ledPin11 = 11;    // the number of the LED pin


// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status

int brightness = 0;  // Starting brightness of the led 
int fadeAmount = 1;  // how many points to fade the LED by

void setup() {
  // initialize the LED pins as an output:
  pinMode(ledPin9, OUTPUT); // 
  pinMode(ledPin10, OUTPUT);
  pinMode(ledPin11, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);  // read the state of the pushbutton value: 
  // check if the pushbutton is pressed. If it is, fade through all the leds
  if (buttonState == HIGH) {
    fadeLED(ledPin9); // fade led on pin 9
    fadeLED(ledPin10); // fade led on pin 10
    fadeLED(ledPin11); // fade led on pin 11
  } else {
    digitalWrite(ledPin9, LOW);
    digitalWrite(ledPin10, LOW);
    digitalWrite(ledPin11, LOW);
  }
  
}

void fadeLED(int LEDnum) {
    int brightness = 0;  // sets the initial brightness to zero
    for (int i = 0; i < 255 * 2; i++) { // Goes through a cycle of getting brighter then dimmer
      analogWrite(LEDnum, brightness);    // set the brightness of pin 9:
      brightness = brightness + fadeAmount;     // change the brightness for next time through the loop:

      // reverse the direction of the fading at the ends of the fade:
      if (brightness <= 0 || brightness >= 255) {
        fadeAmount = -fadeAmount; // Changes the fade amount to be inverse, so that it reverses direction
      }
      delay(1); // Adds a delay before changing the brightness again. Makes the fade slower
    }
    digitalWrite(LEDnum, 0); // Resets the led to be off
}
