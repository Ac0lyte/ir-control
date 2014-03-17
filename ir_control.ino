/* IR Decoder using RadioShack #276-640

   Many thanks to Mark aka "pscmpf" his
   script help flatten my leanring curve.
   It can be found at:
   http://pscmpf.blogspot.com/2010/01/arduino-and-ir-receiver.html
   
   This is my attempt to use the RS IR decoder
   and a spare (read missed by the car thieves
   who took the stero) IR remote control to 
   control stuff.

   I put the whole thing in a standalone homebrew "Arduino"
   and connect to it via the serial interface. Kind of a 
   waste of mCPU cycles, but it makes it really easy to 
   interface to other projects.
   
   ---------------------------------------
   Hardware:
      ArduinoMega 2560
      RadioShack IR decoder #276-640
      1k ohm resister
      Small bits of wire
      Breadboard
      Pioneer Remote Control - CXC5719
   ---------------------------------------
   RadioShack #276-640:
                    
                    +-------+
   output ----------|       |  with IR
   ground ----------|  ( )  |  bubble
   5v+ -------------|       |  facing
                    +-------+  you.
                    
   
   ---------------------------------------
   Circuit:

   5v+ Pin  ---------- IR v+
   Gnd Pin  ---------- IR gnd
   pinData  ---(1k)--- IR out   
   
   ---------------------------------------

*/


//setup variables
int pinData = 2;
int byteValue = 0;

// This is the delay between each value sent.
// Any values read during this time will be
// tossed out. Consider it a de-bounce.
int sensitivity = 100; // in millisec.

void setup() {
  pinMode(pinData, INPUT);  
  Serial.begin(115200);
}

// These need to be unsigned so that they loop to zero
// NOT to a large negative... trust me on this.
unsigned int old_millis = 0;
unsigned int new_millis = 0;


// Read the IR port
// If we have data
//   get the current time
//   if current time less then old time + de-bounce
//     send the data
//     set old time to the current time
//   toss the data, sent or not.

void loop() {
  read_ir();
  if( byteValue ) {
    new_millis = millis();

    // Needed to keep old_millis from getting stuck high.
    if( new_millis < old_millis )
      old_millis = new_millis;
      
    if( new_millis > (old_millis + sensitivity) ) {
      Serial.write(byteValue);
      Serial.flush();
      old_millis = new_millis;
    }
    
    byteValue = 0;
  }
}

// The following code is thanks to Mark aka "pscmpf".
// Thanks for putting it on the web!

void read_ir() {
  unsigned long lengthHeader;
  unsigned long bit;
  
  //look for a header pulse from the IR Receiver
  lengthHeader = pulseIn(pinData, LOW);
  if(lengthHeader > 5000) {
    //step through each of the 32 bits that streams from the remote
    byteValue = 0;
    for(int i = 1; i <= 32; i++) {
      bit = pulseIn(pinData, HIGH);

      //read the 8 bits that are specifically the key code
      //use bitwise operations to convert binary to decimal
      if (i > 16 && i <= 24)
        if(bit > 1000)
          byteValue = byteValue + (1 << (i - 17)); 
    }
  }
}


