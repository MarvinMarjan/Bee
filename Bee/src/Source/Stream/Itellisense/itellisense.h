#pragma once

#include <iostream>
#include <string>

#include "itellisense_buffer.h"

#include "../istream.h"

#include "../../Util/string_util.h"

#include "../ostream_snippet.h"
#include "../ostream_clr.h"

namespace it
{
	std::string get_line_itelli(Itelli_Buffer it_buff)
	{
		std::cout << os::save_c();

		std::string buffer = "";
		char ch;

		do {
			ch = is::get_ch();

			if (ch == is::Backspace) buffer = util::erase_last(buffer);
			else if (ch != is::Enter) buffer += ch;

			std::cout << os::load_c() << os::del_ln(0) << buffer;
		} while (ch != is::Enter);

		std::cout << std::endl;

		return buffer;
	}
}