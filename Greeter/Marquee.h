#pragma once

#include <TM74HC595Display.h>

class Marquee
{
	const int STACK_SIZE = 4;
	const int LAST = STACK_SIZE - 1;
	const int COLS[4] = { 0b1000, 0b0100, 0b0010, 0b0001};
	int char_stack[4] = { 0xff, 0xff, 0xff, 0xff };
	TM74HC595Display *display;
	void realloc();
public:
	Marquee();
	void bind(TM74HC595Display *output);
	void put(int chr);
	void render();

	~Marquee();
};

