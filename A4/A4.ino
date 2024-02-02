// Import packages
#include <CapacitiveSensor.h>
#include <Servo.h> 

// Declare Servo 
Servo myServo;

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);    	// 1 megohm resistor between pins 4 & 2, pin 2 is sensor pin, add wire, metal thing

// Variables for calibration
int max = 0; 
int min = 1023;
long touchValue;
int toMove;


void setup() {
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF); 	// turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600); // for monitor
   myServo.attach(9); // Set servo pin
   recalibrate(); // calibrate sensor
}

void loop()               	 
{
  //
	touchValue =  cs_4_2.capacitiveSensor(30); // get value from capacitive sensor

	Serial.println(touchValue);            	// print sensor output 1
	delay(10);                         	// arbitrary delay to limit data to serial port

  // Map the value so that we can use an easy scale
  toMove = map(touchValue, min, max, 0, 10);
  
  // Check if being touched
  if (toMove >= 4) {
    myServo.write(180); // Rotate counter clockwise
  } else {
    myServo.write(0); // Rotate clockwise
  }
}

// Recalibrates the min and max using data over the next 10 seconds
void recalibrate() {
  // loops through 100 times (100ms each time is 10 seconds total)
  for (int time = 0; time < 100; time++) {
    // Get the current temp from the A0 port
    touchValue =  cs_4_2.capacitiveSensor(30);

    // Check if temp is new max
    if (touchValue > max) {
      // set min
      max = touchValue;
    }
    // Check if temp is new min
    if (touchValue < min) {
      // set min
      min = touchValue;
    }
    // wait 100 ms
    delay(100);
  }
}