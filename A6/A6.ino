const int BUTTON_PIN = 2;
const int SERVO_PIN = 9;
// const String X_PIN = A0;
// const String Y_PIN = A2;
const int P5_PIN = 10;
int incomingByte; // variable for reading from serial port - from p5.js 
int led2brightness = 0; // set up another variable for visualize second LED's brightness


void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(P5_PIN, OUTPUT);
}

void loop()
{
  Serial.println(digitalRead(BUTTON_PIN));

  if (Serial.available() > 0) {   // if there's serial data 
    int inByte = Serial.read(); // read it
    if (Serial.read() == 3) {
      digitalWrite(10, HIGH);
    } else {
      digitalWrite(10, LOW);
    }
 }


  delay(50);
}