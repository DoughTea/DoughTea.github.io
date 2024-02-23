const int P5_PIN = 10; // LED out from computer
int incomingByte; // variable for reading from serial port - from p5.js 
int led2brightness = 0; // set up another variable for visualize second LED's brightness

int boxX = 0; // box x position
int boxY = 0; // boy y position

void setup()
{
  Serial.begin(9600); // set speed of output
  pinMode(P5_PIN, OUTPUT); // Output pin from computer for led
}

void loop() {
  boxX = map(analogRead(A0), 0, 1023, -10, 10); // map joystick x value to -10 through 10
  boxY = map(analogRead(A1), 0, 1023, -10, 10); // map joystick y value to -10 through 10

  Serial.print(boxX); // print x val
  Serial.print(","); // comma for array
  Serial.println(boxY); // print y val
  delay(50); // wait

  if (Serial.available() > 0) {   // if there's serial data 
    char inByte = Serial.read(); // read it
    if (inByte == '3') { // check if serial data is 3
      digitalWrite(10, HIGH); // if it is then turn on led
      delay(100); // wait
    } else {
      digitalWrite(10, LOW); // otherwise keep it off.
    }
 }
}
