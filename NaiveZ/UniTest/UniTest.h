#pragma once

#include <Windows.h>

namespace NaiveZ3D
{
	namespace UniTest
	{
		class UniTest
		{
		public:
			enum class ConsoleColor
			{
				WHITE,
				RED,
				GREEN,
			};
		public:
			static bool Test() { return true; };
			static void SetConsoleColor(ConsoleColor c = ConsoleColor::WHITE)
			{
				HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);
				int color;
				if (c == ConsoleColor::WHITE)
					color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
				else if (c == ConsoleColor::RED)
					color = FOREGROUND_RED;
				else if (c == ConsoleColor::GREEN)
					color = FOREGROUND_GREEN;
				SetConsoleTextAttribute(hdl, color | FOREGROUND_INTENSITY);
			}
		};
	}
}