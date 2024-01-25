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
const int ledPin0 = 10;    // the number of the LED pin
const int ledPin1 = 11;    // the number of the LED pin
const int ledPin2 = 12;    // the number of the LED pin
const int ledPin3 = 13;    // the number of the LED pin

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status

int brightness = 0;  // Starting brightness of the led 
int fadeAmount = 1;  // how many points to fade the LED by


int max = 0; 
int min = 1023;
int mid = 0;
int mid25 = 0;
int mid75 = 0;
int temp = 0;

void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps:

  // initialize the LED pins as an output:
  pinMode(ledPin0, OUTPUT); // 
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  
  // We COULD do a bunch of reading for the first couple of seconds to calibrate
  recalibrate();
}

void loop() {
  temp = analogRead(A0);
  Serial.println(temp);
  
  displayTemp(temp);
}


void displayTemp(int temp) {
  if (min < temp && temp <= mid25) {
    digitalWrite(ledPin0, HIGH);
  } 
  if (mid25 <= temp && temp <= mid) {
    digitalWrite(ledPin1, HIGH);
  }
  if (mid <= temp && temp <= mid75) {
    digitalWrite(ledPin2, HIGH);
  }
  if (temp >= mid75) {
    digitalWrite(ledPin3, HIGH);
  }
  delay(10);
  digitalWrite(ledPin0, LOW);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
}

void recalibrate() {
  for (int time = 0; time < 100; time++) {
    temp = analogRead(A0);
    if (temp > max) {
      max = temp;
    }
    if (temp < min) {
      min = temp;
    }
    delay(100);
  }

  mid = (max + min) / 2;
  mid25 = (min + mid) / 2;
  mid75 = (mid + max) /2; 
}
