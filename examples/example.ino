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