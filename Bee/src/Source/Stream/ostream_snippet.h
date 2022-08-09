#pragma once

#include <iostream>
#include <string>

#include "../../System/Handle/path_handling.h"

#include "ostream_clr.h"

#define DEL_LN_0 "\033[0K"
#define DEL_LN_1 "\033[1K"
#define DEL_LN_2 "\033[2K"

#define DEL_WIN_0 "\033[0J"
#define DEL_WIN_1 "\033[1J"
#define DEL_WIN_2 "\033[2J"
#define DEL_WIN_3 "\033[3J"

#define LINE_UP "\033[A"

namespace os
{
	inline std::string path(hand::Path path)
	{
		return path.get_path() + clr(" $ ", Color::WT_YELLOW);
	}

	/*
	* del_ln modes:
	* 
	* 0: clear from cursor to the end of the line
	* 1: clear from cursor to beginning of the line
	* 2: clear entire line
	* 
	*/

	inline std::string del_ln(unsigned int mode)  { return "\033[" + std::to_string(mode) + 'K'; }

	/*
	* del_win modes:
	* 
	* 0: clear from cursor to end of screen
	* 1: clear from cursor to beginning of the screen
	* 2: clear entire screen
	* 
	*/

	inline std::string del_win(unsigned int mode) { return "\033[" + std::to_string(mode) + 'J'; }

	inline std::string up_ln() { return LINE_UP; }

	inline std::string c_move(unsigned int col) { return "\033[" + std::to_string(col) + "G"; }
	inline std::string l_move(unsigned int ln)  { return "\033[" + std::to_string(ln) + ";H"; }

	inline std::string save_c() { return "\033[s"; }
	inline std::string load_c() { return "\033[u"; }

	inline std::string scroll_dw(unsigned int lines) { return "\033[" + std::to_string(lines) + "T"; }
	inline std::string scroll_up(unsigned int lines) { return "\033[" + std::to_string(lines) + "S"; }
}