import processing.serial.*;
 
 Serial myPort;        // The serial port
 int xPos = 1;         // horizontal position of the graph
 
 void setup () {
 // set the window size:
 size(400, 400);        
 
 myPort = new Serial(this, "/dev/ttyACM4", 115200);
 // don't generate a serialEvent() unless you get a newline character:
 myPort.bufferUntil('\n');
 // set inital background:
 background(0);
 fill(50,255,100);
 ellipse(.5*width,.5*height, 10, 10);
 }
 void draw () {
 // everything happens in the serialEvent()
 }
 
 void serialEvent (Serial myPort) {
 // get the ASCII string:
 String cordinates = myPort.readStringUntil('\n');
 println(cordinates);
 String cordinate[] = split(cordinates, ",");
 
 print(cordinate[0]);
 print(" ");
 println(cordinate[1]);
 
 String xString = cordinate[0], yString = cordinate[1];
 
 if (xString != null && yString != null) {
   // trim off any whitespace:
   xString = trim(xString);
   float x = float(xString);
   yString = trim(yString);
   float y = float(yString);
   
   
   ellipseMode(RADIUS);  // Set ellipseMode to RADIUS
   fill(255);  // Set fill to white
   stroke(0,0,0,0);
   ellipse(x+.5*width, y+.5*height, 2, 2);
   
   }
 }
