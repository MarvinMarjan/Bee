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
		size_t index = 0;
		size_t col = 0;

		char ch;

		do {
			if (index >= buffer.size()) std::cout << os::clr(" ", os::RED, os::ColorMode::UNDERLINE);

			ch = is::get_ch();

			switch ((int) ch)
			{
			case is::Arrow:
				ch = is::get_ch();

				if ((int)ch == is::ArrowUp && it_buff.size() > 0) {
					it_buff.buff_dw();
					buffer = it_buff.buff_get().get();
					index = buffer.size() - 0;
				}

				else if ((int)ch == is::ArrowDown && it_buff.size() > 0) {
					it_buff.buff_up();
					buffer = it_buff.buff_get().get();
					index = buffer.size() - 0;
				}

				else if ((int)ch == is::ArrowLeft) {
					std::cout << os::cmove_left();
					if (index > 0) index--;
					if (col < buffer.size()) col++;
				}

				else if ((int)ch == is::ArrowRight) {
					if (index < buffer.size()) index++;
					if (col > 0) col--;
				}

				break;

			default:
				if (ch == is::Backspace) {
					buffer = util::erase_ch(buffer, index);
					if (index > 0) index--;
				}
				else if (ch != is::Enter) {
					buffer = util::insert_ch(buffer, ch, index);
					index++;
				}
			}

			std::cout << os::load_c() << os::del_win(0);
			
			for (size_t i = 0; i < buffer.size(); i++) //<< os::cmove_left(col);
			{
				if (i == index) {
					std::string s_ch(1, buffer[i]);
					std::cout << os::clr(s_ch, os::RED, os::ColorMode::UNDERLINE);
				}

				else std::cout << buffer[i];
			}

		} while (ch != is::Enter);

		std::cout << std::endl;

		return buffer;
	}
}