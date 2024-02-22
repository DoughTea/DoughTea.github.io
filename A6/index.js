const BAUD_RATE = 9600; // This should match the baud rate in your Arduino sketch

let port, connectBtn; // Declare global variables

var outData; // for data output

let bx;
let by;
let boxSize = 75;
let overBox = false;
let locked = false;
let xOffset = 0.0;
let yOffset = 0.0;

// const serial = new p5.WebSerial();

function setup() {
  setupSerial(); // Run our serial setup function (below)

  // Create a canvas that is the size of our browser window.
  // windowWidth and windowHeight are p5 variables
  createCanvas(windowWidth, windowHeight);

  // p5 text settings. BOLD and CENTER are constants provided by p5.
  // See the "Typography" section in the p5 reference: https://p5js.org/reference/
  textFont("system-ui", 50);
  textStyle(BOLD);
  textAlign(CENTER, CENTER);

  bx = width / 2.0;
  by = height / 2.0;
  rectMode(RADIUS);
  strokeWeight(2);

  // serial.getPorts();
  port.write(3)
}

function draw() {
  const portIsOpen = checkPort(); // Check whether the port is open (see checkPort function below)
  if (!portIsOpen) return; // If the port is not open, exit the draw loop

  let str = port.readUntil("\n"); // Read from the port until the newline
  if (str.length == 0) return; // If we didn't read anything, return.

  // trim the whitespace (the newline) and convert the string to a number
  const arduinoInput = Number(str.trim());

  console.log(arduinoInput) // show in cosole what the arduino is printing

  // Change text and colors based on button state. In p5, you can set colors
  // using standard CSS color names as well as many other color formats.
  if (arduinoInput === 0) {
    // If the button is not pressed
    background("darkcyan"); // Background color
    fill("coral"); // Fill color for the text
    text("not pressed", windowWidth / 2, windowHeight / 2); // Position text in center of the screen
  } else if (arduinoInput === 1) {
    // If the button is pressed
    background("lightskyblue"); // Background color
    fill("yellow"); // Fill color for the text
    text("pressed!", windowWidth / 2, windowHeight / 2); // Position text in center of the screen
  } 
  
  if ( // Test if the cursor is over the box
    mouseX > bx - boxSize &&
    mouseX < bx + boxSize &&
    mouseY > by - boxSize &&
    mouseY < by + boxSize
  ) {
    port.write(3);
  } else {
    port.write(0);
  }
  rect(bx, by, boxSize, boxSize);
}

// Three helper functions for managing the serial connection.

function setupSerial() {
  port = createSerial();

  // Check to see if there are any ports we have used previously
  let usedPorts = usedSerialPorts();
  if (usedPorts.length > 0) {
    // If there are ports we've used, open the first one
    port.open(usedPorts[0], BAUD_RATE);
  }

  // create a connect button
  connectBtn = createButton("Connect to Arduino");
  connectBtn.position(5, 5); // Position the button in the top left of the screen.
  connectBtn.mouseClicked(onConnectButtonClicked); // When the button is clicked, run the onConnectButtonClicked function
}

function checkPort() {
  if (!port.opened()) {
    // If the port is not open, change button text
    connectBtn.html("Connect to Arduino");
    // Set background to gray
    background("gray");
    return false;
  } else {
    // Otherwise we are connected
    connectBtn.html("Disconnect");
    return true;
  }
}

function onConnectButtonClicked() {
  // When the connect button is clicked
  if (!port.opened()) {
    // If the port is not opened, we open it
    port.open(BAUD_RATE);
  } else {
    // Otherwise, we close it!
    port.close();
  }
}

function keyPressed() {
	console.log("writing key");
	port.write('3');
}
