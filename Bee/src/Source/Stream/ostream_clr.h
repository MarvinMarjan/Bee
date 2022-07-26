#pragma once

#include <string>

namespace os
{
	enum Color
	{
		RED = 31,
		GREEN,
		YELLOW,
		BLUE,
		PURPLE,
		CYAN,

		WT_RED = 91,
		WT_GREEN,
		WT_YELLOW,
		WT_BLUE,
		WT_PURPLE,
		WT_CYAN
	};

	enum ColorMode
	{
		NORMAL,
		BOLD,
		DARK,
		ITALIC,
		UNDERLINE,
		TOGGLE,
		TOGGLE2,
		INVERT,
		VOID,
		CROSSED
	};

	inline std::string clr(std::string stream, Color color, ColorMode color_mode = NORMAL)
	{
		return "\033[" + std::to_string(color_mode) + ';' + std::to_string(color) + 'm' + stream + "\033[0m";
	}
}