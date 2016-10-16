#include "beep.h"
#include "Arduino.h"

/**
	Create a new beep manager for the buzzer on the supplied pin
 */
Beep::Beep(int pin): pin(pin) {
	// Configure the pin as output
	pinMode(pin, OUTPUT);

	patternInterval = 300;
	nextOperationTime = 0;

	operationStartIndex = 0;
	operationsLength = 0;
}

/**
	Set the delay interval between patterns
 */
void Beep::setPatternInterval(int delay) {
	patternInterval = delay;
}

/**
	Add a preset that can easily be triggered
 */
void Beep::addPreset(int key, int *pattern, int pattern_length) {
	// Build the preset
	BeepPreset preset;
	preset.key = key;
	preset.pattern = new int[pattern_length];
	preset.pattern_length = pattern_length;

	memcpy(preset.pattern, pattern, pattern_length * sizeof(int));
	
	// Store the preset
	presets.push_back(preset);
}

/**
	Add an operation to the operation queue
 */
void Beep::queueOperation(int operation) {
	// Assign the next operation, after the start index has been incremented
	operationBuffer[(operationStartIndex + operationsLength) % (sizeof(operationBuffer) / sizeof(*operationBuffer))] = operation;
	
	// Increment the operations length
	operationsLength++;
}

/**
	Dequeue an operation, removing it from the queue
 */
int Beep::dequeOperation() {
	int op = operationBuffer[operationStartIndex % (sizeof(operationBuffer) / sizeof(*operationBuffer))];

	// Increment the start index, since that operation has been consumed
	operationStartIndex++;
	// Decrement the operations length, since there is now n-1 operations
	operationsLength--;

	return op;
}

/**
	Clear the buffer by resetting the indices
 */
void Beep::clearBuffer() {
	operationStartIndex = 0;
	operationsLength = 0;
}

// Example pattern: 100, 100, 100

/**
Queue a beep pattern to run as soon as possible
 */
void Beep::beep(int pattern[], int patternLength) {
	for(int i = 0; i < patternLength; i++) {
		if(i % 2 == 0) {
			queueOperation(pattern[i]);
		}
		else {
			queueOperation(-pattern[i]);
		}
	}

	// Add the pattern interval delay
	queueOperation(-patternInterval);
}

/**
Queue a beep from the stored presets
 */
void Beep::beep(int presetKey) {
	for(int i = 0; i < presets.size(); i++) {
		if(presets[i].key == presetKey) {
			// Use the other beep override to queue the pattern
			beep(presets[i].pattern, presets[i].pattern_length);

			break;
		}
	}
}

/**
	Process a loop
 */
void Beep::loop() {
	// If there are operations, and the next operation time is in the past
	if(operationsLength > 0 && nextOperationTime <= millis()) {
		int op = dequeOperation();

		// If the operation is positive, write the buzzer pin HIGH
		if(op > 0) {
			digitalWrite(pin, HIGH);
		}
		else {
			digitalWrite(pin, LOW);
		}

		// Set the next operation time to the current time plus how long the operation is
		nextOperationTime = millis() + abs(op);
	}
}