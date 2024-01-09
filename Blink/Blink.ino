/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.
  There are three LEDs, using pins 13 through 11.
  It turns on and off pin 13, then does the same for 12, and lastly the same for 11.

  check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman
  modified 8 Jan 2024
  by Andrew Doty
*/

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  // initialize digital pin LED_BUILTIN as an output.
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, HIGH);  // turn the LED connected to the 13th pin on 
  delay(500);                      // wait for half a second
  digitalWrite(13, LOW);  // turn the LED connected to the 13th pin off 

  digitalWrite(12, HIGH);  // turn the LED connected to the 12th pin on
  delay(500);                      // wait for half a second
  digitalWrite(12, LOW);  // turn the LED connected to the 13th pin off

  digitalWrite(11, HIGH);  // turn the LED connected to the 11th pin on
  delay(500);                      // wait for half a second
  digitalWrite(11, LOW);  // turn the LED connected to the 11th pin off
}
