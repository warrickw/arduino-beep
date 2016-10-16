Arduino Beep Pattern
==============

Simple library for writing digital on-off patterns to a Arduino digital pin, which could be a buzzer or LED or anything else.

###Pattern definition
Beep patterns are defined as a sequency of on-off time's... for example, the following int array
defines a on-off-on-off pattern with 100ms on, 100ms off, and 100ms on (then an assumed off...)

```C++
int pattern[] = { 100, 100, 100 };
```
It is important to note that the pattern should ALWAYS end with an on time (always an odd length), since the off is assumed.
All time intervals are in milliseconds;



###Usage

Include the library, and its depencancy 

Create an instance of Beep - providing the pin number to use for digital output

```C++
// Initialize a beep manager on digital pin 12
Beep beep(12)
```

Queue a beep pattern - this will cause it to be run strait away if there is nothing else still running

```C++
// Define a simple pattern
int pattern[] = { 100, 100, 100 };

// Queue the pattern, providing the pattern and the length of the pattern
beep.beep(pattern, 3);
```

Patterns can also be registered as presets (you might do this in setup()) to make it easy to reuse
patterns and simplify playing them back.

```C++
// Define a simple pattern
int pattern[] = { 100, 100, 100 };

// Register the pattern as pattern '2' (arbituary int)
beep.addPreset(2, pattern, 3);

// Play preset 2 - the pattern registered above
beep.beep(2);
```

Setting the minumum delay between different patterns (defaultly 400 or so milliseconds). This will only be noticable 
if two patterns are queued at the same time... they will be played back syncronously with a 400ms delay between them.

```C++
// Set the delay between patterns to 400ms
beep.setPatternInterval(400);
```

###Example Arduino sketch

The following is also provided in the library 'examples' folder.

```C++
// Include the Vector dependancy (available at https://github.com/zacsketches/Arduino_Vector/blob/master/README.md)
#include "Vector.h"
// Include the beep library
#include "beep.h"

Beep beep(12);

void setup() {
  // Define a simple pattern with a single 100ms on pulse
  int pattern[] = { 100 };
  
  // Register the pattern as a preset number 1
  beep.addPreset(1, pattern, 3);
}

void loop() {
  // Define a simple pattern
  int pattern[] = { 100, 100, 100 };
  
  // Queue the pattern directly
  beep.beep(pattern, 3);
  
  
  // Queue a previously defined preset (defined in setup() in this example()
  beep.beep(1);
}
```

Installation
==============

1. From the command line 'cd' into the Arduino/libraries folder.
2. Enter 'git clone https://github.com/warrickw/arduino-beep'
3. This will clone the library into your Arduino libraries.
4. Restart the Arduino IDE.

Make sure you have also installed Beep's depencancy on Arduino_Vector (in the same manner), available at
https://github.com/zacsketches/Arduino_Vector