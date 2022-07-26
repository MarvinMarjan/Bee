#include <iostream>
#include <string>

#include "../../System/Handle/path_handling.h"

#include "ostream_clr.h"

#define DEL_LN_0 "\033[0K"
#define DEL_LN_1 "\033[1K"
#define DEL_LN_2 "\033[2K"

#define LINE_UP "\033[A"

namespace os
{
	inline std::string path(hand::Path path)
	{
		return path.get_path() + clr(" $ ", Color::WT_YELLOW);
	}

	inline std::string del_ln(unsigned int mode) { return "\033[" + std::to_string(mode) + 'K'; }

	inline std::string up_ln() { return LINE_UP; }

	inline std::string c_move(unsigned int col) { return "\033[" + std::to_string(col) + "G"; }
}