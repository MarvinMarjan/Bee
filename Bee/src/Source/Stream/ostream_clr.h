#pragma once

#include <string>

namespace os
{
	enum Color
	{
		Null = 0,

		RED = 31,
		GREEN,
		YELLOW,
		BLUE,
		PURPLE,
		CYAN,
		WHITE,

		GRAY = 90,
		WT_RED ,
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
		TOGGLE_SLOW,
		TOGGLE_RAPID,
		INVERT,
		_VOID,
		CROSSED
	};

	inline std::string clr(std::string stream, Color color, ColorMode color_mode = NORMAL)
	{
		return "\033[" + std::to_string(color_mode) + ';' + std::to_string(color) + 'm' + stream + "\033[0m";
	}

	inline std::string get_clr(Color color = Null, ColorMode color_mode = NORMAL)
	{
		return ((color == Null) ? "\033[0m" : "\033[" + std::to_string(color_mode) + ';' + std::to_string(color) + 'm');
	}
}