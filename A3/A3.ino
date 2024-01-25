// Andrew Doty wi24
// HCDE 439
// 1/26/2024

// constants won't change. They're used here to set pin numbers:
const int ledPin0 = 10;    // the number of the LED pin
const int ledPin1 = 11;    // the number of the LED pin
const int ledPin2 = 12;    // the number of the LED pin
const int ledPin3 = 13;    // the number of the LED pin

// Variables for calibrating the max, min, average, 25th percentile, 
//    75th percentile, and current temp 
int max = 0; 
int min = 1023;
int mid = 0;
int mid25 = 0;
int mid75 = 0;
int temp = 0;

// Used by the map function to help in debugging which pattern of LEDs 
//    should be lit
int whichLED = 0;

void setup() {
  // open the serial port at 9600 bps, allows us to see output in the console
  Serial.begin(9600); 

  // initialize the LED pins as an output:
  pinMode(ledPin0, OUTPUT); // 
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  
  // Calls the recalibrate function to find max, min, average, 25th percentile,
  //    75th percentile, and current temp 
  recalibrate();
}

// Main loop that the code runs through
void loop() {
  // Reads the value at the A0 port
  temp = analogRead(A0);
  // Maps the current temp to the range of possible led combos
  whichLED = map(temp, min, max, 0, 7);

  // Prints out information for debugging
  Serial.print(temp);
  Serial.print(" : ");
  Serial.println(whichLED);
  
  // Calls the displayTemp function which takes the current 
  //    temperature and determines which leds to light up 
  displayTemp(temp);
}


// Based on the input temperature determines which LEDs should light up
void displayTemp(int temp) {
  // If the temp is higher than min and at or lower than the 25th percentile
  if (min < temp && temp <= mid25) {
    // lights up blue LED
    digitalWrite(ledPin0, HIGH);
  } 
  // If the temp is between the 25th percentile and average (Inclusive)
  if (mid25 <= temp && temp <= mid) {
    // Light up yellow LED
    digitalWrite(ledPin1, HIGH);
  }
  // If the temp is between the average and 75th percentile (Inclusive)
  if (mid <= temp && temp <= mid75) {
    // Light up the red LED
    digitalWrite(ledPin2, HIGH);
  }
  // If the temp is at or higher than the 75th percentile
  if (temp >= mid75) {
    // Light up white LED
    digitalWrite(ledPin3, HIGH);
  }
  // Add a delay for smoothing
  delay(100);

  // Turn off all the LEDs (for easy reset)
  digitalWrite(ledPin0, LOW);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
}

// Recalibrates the min and max using data over the next 10 seconds
void recalibrate() {
  // loops through 100 times (100ms each time is 10 seconds total)
  for (int time = 0; time < 100; time++) {
    // Get the current temp from the A0 port
    temp = analogRead(A0);

    // Check if temp is new max
    if (temp > max) {
      // set min
      max = temp;
    }
    // Check if temp is new min
    if (temp < min) {
      // set min
      min = temp;
    }
    // wait 100 ms
    delay(100);
  }

  // After the loop does some math to find the 25th, 50th, and 75th percentiles
  mid = (max + min) / 2;
  mid25 = (min + mid) / 2;
  mid75 = (mid + max) /2; 
}


22 : 12
22 : 12
22 : 12
21 : 9
23 : 15
21 : 9
23 : 15
21 : 9
22 : 12