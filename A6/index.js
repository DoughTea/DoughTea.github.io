const BAUD_RATE = 9600; // This should match the baud rate in your Arduino sketch

let port, connectBtn; // Declare global variables

var outData; // for data output

let bx; // box x
let by; //bo y
let boxSize = 75; // box size
let xOffset = 0.0; // box x
let yOffset = 0.0; // boy y
let input = [0, 0, 0]; // input format light, x, y

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

  // set initial box location to middle of page
  bx = width / 2.0;
  by = height / 2.0;
  rectMode(RADIUS); // determins how the rectangle parameters are interpreted
  rect(Number(bx), Number(by), 20, 20); // draw rectangle
  strokeWeight(2); // sets outlike
}

function draw() {
  const portIsOpen = checkPort(); // Check whether the port is open (see checkPort function below)
  if (!portIsOpen) return; // If the port is not open, exit the draw loop

  let str = port.readUntil("\n"); // Read from the port until the newline
  if (str.length == 0) return; // If we didn't read anything, return.

  // Read the input and extract the x and y
  let arr = str.trim().split(","); 
  bx = Number(bx) + Number(arr[1]); // change the bx, x amount
  by = Number(by) + Number(arr[2]); // change the by, y amount
  rect(bx, by, 20, 20); // draw the rectangle

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
  // when the key is pressed, output three so the led lights
  for (i = 0; i < 10; i++) { // do it for a bit so the led stays lit for a little
    port.write('3');
  }
}
