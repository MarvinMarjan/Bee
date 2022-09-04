#pragma once

#include "../Stream/ostream_clr.h"
#include "../Util/string_util.h"

#include <string>
#include <vector>
#include <map>

namespace util
{
	std::vector<std::string> get_query_list(std::string word, std::vector<std::string> list)
	{
		std::vector<std::string> q_list;
		bool passed = false;

		if (word.size() == 0) return list;

		for (size_t i = 0; i < list.size(); i++)
			for (size_t o = 0; o < word.size(); o++)
			{
				if (list[i][o] == word[o]) passed = true;
				else break;
				if (o + 1 >= word.size() && passed) q_list.push_back(list[i]);
			}

		return q_list;
	}

	os::Color string_to_color(std::string src)
	{
		if (src == "Null")           return os::Null;

		else if (src == "RED")       return os::RED;
		else if (src == "GREEN")     return os::GREEN;
		else if (src == "YELLOW")    return os::YELLOW;
		else if (src == "BLUE")      return os::BLUE;
		else if (src == "PURPLE")    return os::PURPLE;
		else if (src == "CYAN")      return os::CYAN;
		else if (src == "WHITE")     return os::WHITE;
								     
		else if (src == "GRAY")      return os::GRAY;
		else if (src == "WT_RED")    return os::WT_RED;
		else if (src == "WT_GREEN")  return os::WT_GREEN;
		else if (src == "WT_YELLOW") return os::WT_YELLOW;
		else if (src == "WT_BLUE")   return os::WT_BLUE;
		else if (src == "WT_PURPLE") return os::WT_PURPLE;
		else if (src == "WT_CYAN")   return os::WT_CYAN;

		return os::Nothing;
	}

	std::string color_to_string(os::Color src)
	{
		switch (src)
		{
		case os::Nothing:   return "Nothing";
		case os::Null:      return "Null";

		case os::RED:       return "RED";
		case os::GREEN:     return "GREEN";
		case os::YELLOW:    return "YELLOW";
		case os::BLUE:      return "BLUE";
		case os::PURPLE:    return "PURPLE";
		case os::CYAN:      return "CYAN";
		case os::WHITE:     return "WHITE";
								   
		case os::GRAY:      return "GRAY";
		case os::WT_RED:    return "WT_RED";
		case os::WT_GREEN:  return "WT_GREEN";
		case os::WT_YELLOW: return "WT_YELLOW";
		case os::WT_BLUE:   return "WT_BLUE";
		case os::WT_PURPLE: return "WT_PURPLE";
		case os::WT_CYAN:   return "WT_CYAN";
		}

		return "";
	}

	os::ColorMode string_to_color_mode(std::string src)
	{
		if (src == "NORMAL") return os::NORMAL;
		else if (src == "BOLD") return os::BOLD;
		else if (src == "DARK") return os::DARK;
		else if (src == "ITALIC") return os::ITALIC;
		else if (src == "UNDERLINE") return os::UNDERLINE;
		else if (src == "TOGGLE_SLOW") return os::TOGGLE_SLOW;
		else if (src == "TOGGLE_RAPID") return os::TOGGLE_RAPID;
		else if (src == "INVERT") return os::INVERT;
		else if (src == "NOTHING") return os::NOTHING;
		else if (src == "CROSSED") return os::CROSSED;

		return os::NORMAL;
	}

	std::string color_mode_to_string(os::ColorMode src)
	{
		switch (src)
		{
		    case os::NORMAL: return "NORMAL";
			case os::BOLD: return "BOLD";
			case os::DARK: return "DARK";
			case os::ITALIC: return "ITALIC";
			case os::UNDERLINE: return "UNDERLINE";
			case os::TOGGLE_SLOW: return "TOGGLE_SLOW";
			case os::TOGGLE_RAPID: return "TOGGLE_RAPID";
			case os::INVERT: return "INVERT";
			case os::NOTHING: return "NOTHING";
			case os::CROSSED: return "CROSSED";

			default: return "NORMAL";
		}
	}

	inline os::ColorSet raw_to_color_set(std::string src)
	{
		os::ColorSet color_set;

		for (size_t i = 0; i < src.size(); i++) {
			if (src[i] == '[') color_set.color_mode = os::ColorMode(std::stoi(util::get_until(src, ';', i + 1)));
			if (src[i] == ';') color_set.color = os::Color(std::stoi(util::get_until(src, 'm', i + 1)));
		}

		return color_set;
	}

	inline os::ColorSet semi_raw_to_color_set(std::string src)
	{
		os::ColorSet color_set;

		for (size_t i = 0; i < src.size(); i++) {
			if (src[i] == '\\') color_set.color = util::string_to_color(util::get_until(src, ';', i + 1));
			if (src[i] == ';') color_set.color_mode = util::string_to_color_mode(util::sub_string(src, i + 1, src.size()));
		}

		return color_set;
	}
}