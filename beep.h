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
		Beep(int pin);
		void setPatternInterval(int delay);
		void beep(int pattern[], int patternLength);
		void beep(int presetKey);
		void loop();
		void addPreset(int key, int *pattern, int pattern_length);
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