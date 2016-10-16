#ifndef BEEP_H
#define BEEP_H
#include "Arduino.h"
#include "Vector.h"

struct BeepPreset {
	int *pattern;
	int pattern_length;
	int key;
};

/**
Beep manager
 */
class Beep {
	public:
		// Initialze a beep manager using the provided pin for output
		Beep(int pin);
		// Set the minimum delay (in ms) between patterns
		void setPatternInterval(int delay);
		// Queue a beep pattern
		void beep(int pattern[], int patternLength);
		// Run a beep pattern that was preset
		void beep(int presetKey);
		// Call this every iteration of your arduino sketch's loop
		void loop();
		// Register a beep preset
		void addPreset(int key, int *pattern, int pattern_length);
		// Clear the beep buffer - try not to use this
		void clearBuffer();
	private:
		int pin;
		int patternInterval;
		
		int operationBuffer[64];
		int operationStartIndex;
		int operationsLength;
		void queueOperation(int operation);
		int dequeOperation();

		unsigned long nextOperationTime;
		Vector<BeepPreset> presets;
};

#endif