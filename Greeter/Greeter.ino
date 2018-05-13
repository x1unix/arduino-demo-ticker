/*
 Name:		Greeter.ino
 Created:	13.05.2018 2:58:07
 Author:	x1unix
*/

#include <TM74HC595Display.h>
#include "chars.h"
#include "Marquee.h"

int SCLK = 7;
int RCLK = 6;
int DIO = 5;

// Display instance
TM74HC595Display disp(SCLK, RCLK, DIO);

// Ticker
Marquee marquee;

unsigned char LED_0F[29];

// Message: Hello 101
int charlist[10] = {
	chars::H,
	chars::E,
	chars::L,
	chars::L,
	chars::O,
	chars::Space,
	chars::NUM_1,
	chars::NUM_0,
	chars::NUM_1,
	chars::Space
};

// Last message index
const int LAST_IDX = 10 - 1;

// Current char index
int current_char = 0;

// Next text update time
int time_to_update = 0;

// Text refresh time
const int REFRESH_RATE = 1 * 250;


void setup() {
	// Set ticker to control our display
	marquee.bind(&disp);

	// Set initial update time
	time_to_update = millis();
}

// Returns next char to print
int get_next_char() {
	if (current_char == 0) {
		current_char++;
		return charlist[1];
	}

	if (current_char == LAST_IDX) {
		current_char = 0;
		return charlist[0];
	}

	current_char++;
	return charlist[current_char];
}

// the loop function runs over and over again until power down or reset
void loop() {

	// Push a new char only after a delay
	if (millis() >= time_to_update)
	{
		int chr = get_next_char();
		marquee.put(chr);
		time_to_update += REFRESH_RATE;
	}

	// Render loop
	marquee.render();
}
