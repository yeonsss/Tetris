#pragma once
enum class ConsoleColor
{
	BLACK	= 0,
	RED		= FOREGROUND_RED,
	GREEN	= FOREGROUND_GREEN,
	BLUE	= FOREGROUND_BLUE,
	YELLOW	= RED | GREEN,
	WHITE	= RED | GREEN | BLUE,
};

class ConsoleTool
{
public:
	static void SetCursorPosition(int x, int y);
	static void SetCursorColor(ConsoleColor color);
	static void ShowConsoleCursor(bool flag);
};

