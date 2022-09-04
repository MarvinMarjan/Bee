#pragma once

#include <string>
#include <vector>

namespace os
{
	const std::vector<std::string> STRColors = {
		"RED",
		"GREEN",
		"YELLOW",
		"BLUE",
		"PURPLE",
		"CYAN",
		"WHITE",

		"GRAY",
		"WT_RED",
		"WT_GREEN",
		"WT_YELLOW",
		"WT_BLUE",
		"WT_PURPLE",
		"WT_CYAN"
	};

	const std::vector<std::string> STRColors_mode = {
		"NORMAL",
		"BOLD",
		"DARK",
		"ITALIC",
		"UNDERLINE",
		"TOGGLE_SLOW",
		"TOGGLE_RAPID",
		"INVERT",
		"CROSSED"

	};

	enum Color
	{
		Nothing = -1,

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
		Default = -1,

		NORMAL,
		BOLD,
		DARK,
		ITALIC,
		UNDERLINE,
		TOGGLE_SLOW,
		TOGGLE_RAPID,
		INVERT,
		NOTHING,
		CROSSED
	};

	struct ColorSet {
		os::Color color;
		os::ColorMode color_mode;
	};

	inline std::string clr(std::string stream, Color color, ColorMode color_mode = NORMAL)
	{
		return "\033[" + std::to_string(color_mode) + ';' + std::to_string(color) + 'm' + stream + "\033[0m";
	}

	inline std::string clr(std::string stream, ColorSet color)
	{
		return "\033[" + std::to_string(color.color_mode) + ';' + std::to_string(color.color) + 'm' + stream + "\033[0m";
	}

	inline std::string get_clr(Color color = Null, ColorMode color_mode = NORMAL)
	{
		return ((color == Null) ? "\033[0m" : "\033[" + std::to_string(color_mode) + ';' + std::to_string(color) + 'm');
	}
}