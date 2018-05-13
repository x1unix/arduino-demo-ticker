#include "Marquee.h"
#include <Arduino.h>

void Marquee::realloc()
{
	for (int i = 0; i < LAST; i++) {
		this->char_stack[i] = this->char_stack[i + 1];
	}

	this->char_stack[LAST] = 0;
}

Marquee::Marquee() = default;

// Bind display output to the marquee
void Marquee::bind(TM74HC595Display * output)
{
	this->display = output;
}

// Put new char into the queue
void Marquee::put(int chr)
{
	this->realloc();
	this->char_stack[LAST] = chr;
}

// Render all chars
void Marquee::render()
{
	TM74HC595Display output = *this->display;
	for (int i = 0; i <= LAST; i++)
	{
		output.send(char_stack[i], COLS[i]);
		// Need to keep small delay to keep all chars present
		delay(1);
	}
}

Marquee::~Marquee()
{
}
