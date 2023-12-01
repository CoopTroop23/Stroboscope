# Building a Stroboscope #

A stroboscope is a tool that allows for the approximation of an objects angular rotation rate. This is some janky code I made about a year ago that works ok. The stroboscope can be seen in action in [this video](https://www.youtube.com/watch?v=7cK_2AukqGA) I made. 


## Hardware I used ##
This is a list of parts that I used. Keep in mind that you could use slightly different components and it probably would still work.
* Arduino Uno
* OLED display (128x32)
* Bright LED 
* N Channel MOSFET (IRFZ44N)
* Rotary Encoder (With button included)
* Push button
* 10 kOhm resistor (idk why)


  
## Electrical Wiring ##
Here is a wiring connections I used. I do not recommend using pin 13 to drive the LED. Any time I wanted to upload code the led would blink and it was annoying.

Arduino Pin Number | Component
-------------------|-----------
4                  | Push button
6                  | Encoder CLK pin 
7                  | Encoder DT pin
9                  | Encoder Button pin
13                 | MOSFET that drives LED
A4                 | OLED SDA pin
A5                 | OLED SCL pin

Also don't forget power and ground for all the components!

## Operating ## 
To operate the stroboscope, point the light at a spinning object. Turn the encoder to increase or decrease the frequency of the LED to match the frequency of your object. To find the correct frequency faster, change the increment by pressing down on the encoder button. This will change what frequency range you are looking in. To multiply the frequency by an integer, press the push button (I don't remember why I added this feature).

## Problems ##
The timing of the flashing stroboscope isn't super accurate. This becomes obvious at high frequencies. This probably could be fixed with code but honestly the scope works good enough for me.

