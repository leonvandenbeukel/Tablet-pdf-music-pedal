#include <Bounce2.h>
#include "Keyboard.h"

#define BUTTON_PIN_LEFT 14
#define LED_PIN_LEFT 9
#define BUTTON_PIN_RIGHT 15
#define LED_PIN_RIGHT 10
#define LED_POWER 8

// Keys reference: https://github.com/arduino-libraries/Keyboard/blob/master/src/Keyboard.h
#define PREV_PAGE KEY_LEFT_ARROW     
#define NEXT_PAGE KEY_RIGHT_ARROW

// Instantiate a Bounce object
Bounce debouncer_left = Bounce();
Bounce debouncer_right = Bounce();

// The current buttonState_left
// 0 : released
// 1 : pressed less than 2 seconds
// 2 : pressed longer than 2 seconds
int buttonState_left;
unsigned long buttonPressTimeStamp_left;
int buttonState_right;
unsigned long buttonPressTimeStamp_right;

void setup() {

	Serial.begin(57600);

	// Setup the button
	pinMode(BUTTON_PIN_LEFT, INPUT);
	pinMode(BUTTON_PIN_RIGHT, INPUT);
	// Activate internal pull-up
	digitalWrite(BUTTON_PIN_LEFT, HIGH);
	digitalWrite(BUTTON_PIN_RIGHT, HIGH);

	// After setting up the button, setup debouncer_left
	debouncer_left.attach(BUTTON_PIN_LEFT);
	debouncer_right.attach(BUTTON_PIN_RIGHT);
	debouncer_left.interval(5);
	debouncer_right.interval(5);

	//Setup the LEDs
	pinMode(LED_PIN_LEFT, OUTPUT);
	pinMode(LED_PIN_RIGHT, OUTPUT);
	pinMode(LED_POWER, OUTPUT);

	digitalWrite(LED_POWER, HIGH);

	Keyboard.begin();
}

void loop() {

	// Update the debouncer_left and get the changed state
	boolean changed_left = debouncer_left.update();
	boolean changed_right = debouncer_right.update();

	if (changed_left) {
		// Get the update value
		int value = debouncer_left.read();

		if (value == HIGH) {
			digitalWrite(LED_PIN_LEFT, LOW);

			buttonState_left = 0;
			Serial.println("Button released (state 0)");

		}
		else {
			digitalWrite(LED_PIN_LEFT, HIGH);
			Keyboard.write(PREV_PAGE);
			buttonState_left = 1;
			Serial.println("Button pressed (state 1)");
			buttonPressTimeStamp_left = millis();
		}
	}

	if (changed_right) {
		// Get the update value
		int value = debouncer_right.read();

		if (value == HIGH) {
			digitalWrite(LED_PIN_RIGHT, LOW);

			buttonState_right = 0;
			Serial.println("Button released right (state 0)");

		}
		else {
			digitalWrite(LED_PIN_RIGHT, HIGH);
			Keyboard.write(NEXT_PAGE);
			buttonState_right = 1;
			Serial.println("Button pressed right (state 1)");
			buttonPressTimeStamp_right = millis();
		}
	}
}
