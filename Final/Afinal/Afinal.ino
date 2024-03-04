// set motor pin numbers
int RIGHT_MOTOR = 9;
int RIGHT_MOTOR2 = 11;
int LEFT_MOTOR = 10;
int LEFT_MOTOR2 = 12;

// Set motor pin numbers
int L_EYE = 7;
int R_EYE = 6;

// set button pin number
int BUTTON = 8;

// initialize toggle for go and stop 
bool toggled = false;

// initialize reverse
bool reverse = false;

void setup() {
  // Set up serial Monitor for debugging
  Serial.begin(9600);

  // Set initial pinmodes
  pinMode(RIGHT_MOTOR, OUTPUT);
  pinMode(LEFT_MOTOR, OUTPUT);
  pinMode(RIGHT_MOTOR2, OUTPUT);
  pinMode(LEFT_MOTOR2, OUTPUT);
  pinMode(R_EYE, OUTPUT);
  pinMode(L_EYE, OUTPUT);
  pinMode(BUTTON, INPUT);

  // Turn on eyes
  digitalWrite(R_EYE, HIGH);
  digitalWrite(L_EYE, HIGH);
}


void loop() {
  // Print if button is pressed for testing
  Serial.println(digitalRead(BUTTON));
  
  if (digitalRead(BUTTON) == 1) {
    toggled = !toggled;
  }

  while (toggled) {
    // Run in figure 8 a couple times
    for (int i = 0; i < 2; i++) {
      // turn right
      setMotorR(speed, !reverse);
      setMotorL(speed, reverse);
      delay(500);

      // forward
      setMotorR(speed, !reverse);
      setMotorL(speed, !reverse);
      delay(500);

      // turn left
      setMotorR(speed, reverse);
      setMotorL(speed, !reverse);
      delay(500);

      // forward
      setMotorR(speed, !reverse);
      setMotorL(speed, !reverse);
      delay(500);
    }
  }
}

// Moves the right motor
void setMotorR(boolean reverse) {
  digitalWrite(RIGHT_MOTOR, ! reverse);
  digitalWrite(RIGHT_MOTOR2, reverse);
}

// Moves the left motor
void setMotorL(boolean reverse) {
  digitalWrite(LEFT_MOTOR, ! reverse);
  digitalWrite(LEFT_MOTOR2, reverse);
}
