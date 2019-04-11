#pragma once
#include<Windows.h>
#include<iostream>

enum class TEXT_COLOR
{
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	PINK = 5,
	YELLOW = 6,
	WHITE = 7,
	GRAY = 8,
	BRIGHT_BLUE = 9,
	BRIGHT_GREEN = 10,
	BRIGHT_CYAN = 11,
	BRIGHT_RED = 12,
	BRIGHT_PINK = 13,
	BRIGHT_YELLOW = 14,
	BRIGHT_WHITE = 15
};

class ConsoleController
{
public:
	ConsoleController(void)
	{
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleInfo);
	}

	void SetTextColor(enum class TEXT_COLOR Color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(Color));
	}
	void SetDefaultColor(void)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleInfo.wAttributes);
	}
private:
	CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
};

class ConsoleTextColor
{
public:
	ConsoleTextColor(enum class TEXT_COLOR Color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(Color));
	}
	~ConsoleTextColor()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleInfo.wAttributes);
	}
private:
	CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
};