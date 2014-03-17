IR Decoder using RadioShack #276-640

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


