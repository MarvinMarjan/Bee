#pragma once

#include <iostream>
#include <string>

#include "itellisense_buffer.h"

#include "../istream.h"

#include "../../Util/string_util.h"

#include "../../Data/data.h"

#include "../ostream_snippet.h"
#include "../ostream_clr.h"

namespace it
{
	void itelli_stdin_arrow_config(char ch, std::string& buffer, Itelli_Buffer& it_buff, size_t& index, size_t& col);
	void itelli_stdin_stream_config(char ch, std::string& buffer, Itelli_Buffer& it_buff, size_t& index, size_t& col);

	inline void itelli_draw_caret(os::Color caret_color = os::RED, os::ColorMode caret_color_mode = os::UNDERLINE, char ch = ' ')
	{
		std::cout << os::clr(util::str_char(ch), caret_color, caret_color_mode);
	}

	inline void _checkcaret(size_t i, size_t index, os::Color caret_color = os::RED, os::ColorMode caret_color_mode = os::UNDERLINE, char ch = ' ')
	{
		if (i == index)	itelli_draw_caret(caret_color, caret_color_mode, ch);
	}

	std::string itelli_stdin(dt::DBase dbase, Itelli_Buffer it_buff, os::Color caret_color = os::RED, os::ColorMode caret_color_mode = os::UNDERLINE)
	{
		std::cout << os::save_c();

		std::string buffer = "";
		size_t index = 0;
		size_t col = 0;

		bool draw_caret = true;

		char ch;

		do {
			if (index >= buffer.size()) itelli_draw_caret(caret_color, caret_color_mode);

			ch = is::get_ch();

			if ((int)ch == is::Enter) draw_caret = false;

			itelli_stdin_arrow_config(ch, buffer, it_buff, index, col);

			std::cout << os::load_c() << os::del_win(0);
			
			for (size_t i = 0; i < buffer.size(); i++)
			{
				switch ((int)buffer[i])
				{
				case is::Quote: {
					size_t init_index = i;
					for (i; i < buffer.size(); i++) {
						if (i == index && draw_caret) itelli_draw_caret(caret_color, caret_color_mode, buffer[i]);
						else std::cout << os::clr(util::str_char(buffer[i]), os::GREEN);
					    if ((int)buffer[i] == is::Quote && i != init_index) break;
					}
					break;
				}

				case is::DollarSign: {
					std::string name = "";

					for (size_t o = i + 1; o < buffer.size(); o++) {
						if (buffer[o] == ' ') break;
						name += buffer[o];
					}

					for (i; i < buffer.size(); i++) {
						if (buffer[i] == ' ') break;
						if (i == index && draw_caret) itelli_draw_caret(caret_color, caret_color_mode, buffer[i]);
						else if (dbase.exist_shortcut(name)) std::cout << os::clr(util::str_char(buffer[i]), os::CYAN);
						else std::cout << buffer[i];
					}
				}

				default:
					if (cmd::check(util::split_string(buffer)[0]) != cmd::Not_found && i < util::find_first(buffer, ' '))
						for (i; i < util::find_first(buffer, ' '); i++) {
							if (i >= buffer.size()) break;
							if (i == index && draw_caret) itelli_draw_caret(caret_color, caret_color_mode, buffer[i]);
							else std::cout << os::clr(util::str_char(buffer[i]), os::GRAY);
						}
					
				    if (i == index && draw_caret) itelli_draw_caret(caret_color, caret_color_mode, buffer[i]);
					else std::cout << buffer[i];
				}
			}

		} while (ch != is::Enter);

		std::cout << std::endl;

		return buffer;
	}

	void itelli_stdin_arrow_config(char ch, std::string& buffer, Itelli_Buffer& it_buff, size_t& index, size_t& col)
	{
		switch ((int)ch)
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

		default: itelli_stdin_stream_config(ch, buffer, it_buff, index, col);
		}
	}

	void itelli_stdin_stream_config(char ch, std::string& buffer, Itelli_Buffer& it_buff, size_t& index, size_t& col)
	{
		if (ch == is::Backspace) {
			buffer = util::erase_ch(buffer, index);
			if (index > 0) index--;
		}
		else if (ch != is::Enter) {
			buffer = util::insert_ch(buffer, ch, index);
			index++;
		}
	}
}