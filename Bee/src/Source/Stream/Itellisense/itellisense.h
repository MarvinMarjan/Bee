#pragma once

#include <iostream>
#include <string>

#include "itellisense_substring.h"
#include "itellisense_buffer.h"

#include "../istream.h"

#include "../../Util/itellisense_util.h"
#include "../../Util/string_util.h"
#include "../../Util/array_util.h"

#include "../../Operator/operator.h"
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

	inline void itelli_draw_caret(os::ColorSet caret, char ch = ' ')
	{
		std::cout << os::clr(util::str_char(ch), caret);
	}

	inline void _checkcaret(size_t i, size_t index, os::Color caret_color = os::RED, os::ColorMode caret_color_mode = os::UNDERLINE, char ch = ' ')
	{
		if (i == index)	itelli_draw_caret(caret_color, caret_color_mode, ch);
	}

	std::string itelli_stdin(hand::Path path, dt::DBase& dbase, Itelli_Buffer it_buff, sys::Defs& defs)
	{
		std::cout << os::save_c();
		
		std::string buffer = "";
		std::string sub_str = "";

		std::vector<std::string> cmds = util::map<cmd::CMD_Data, std::string>(cmd::commands, [] (cmd::CMD_Data cmd) { return cmd.name; });
		std::vector<std::string> ents;
		std::vector<std::string> aux;
		Itelli_Buffer query_list;
		std::string sub_bf_str;
		substring sub_bf;
		bool tab_process = false;

		size_t index = 0;
		size_t col = 0;

		bool draw_caret = true;

		char ch;

		do {
			if (index >= buffer.size()) itelli_draw_caret(defs.caret_color);

			set_substring(sub_bf, buffer, ((index == 0) ? index : index - 1));

			ch = is::get_ch();

			if ((int)ch == is::Enter) draw_caret = false;
			else if ((int)ch == is::Tab) {
				bool is_command = (!util::exist_ch(buffer, ' '));

				if (!tab_process) {
					sub_bf_str = util::sub_string(buffer, ((sub_bf.begin == 0) ? sub_bf.begin : sub_bf.begin + 1), sub_bf.end);
					ents = util::get_folder_ent(path.get_path());
					tab_process = true;
				}

				
				aux = util::get_query_list(((util::exist(sub_bf_str, ((is_command) ? cmds : ents)) ? "" : sub_bf_str)), ((is_command) ? cmds : ents));

				for (size_t i = 0; i < aux.size(); i++)
					if (util::find_all(aux[i], ' ').size() != 0 && !is_command) {
						aux[i] = util::insert(aux[i], "\"", 0);
						aux[i] += '\"';
					}

				query_list.set_buff(aux, false);
				
				if (query_list.size() > 0) {
					buffer = util::erase(buffer, sub_bf.begin - ((query_list.buff_get_last().get()[0] == '\"' && query_list.get_itr() != 0) ? 1 : 0), sub_bf.end);
					buffer = util::insert(buffer, ((buffer.size() == 0) ? "" : " ") + query_list.buff_get().get(), sub_bf.begin);
				}

				index = buffer.size();

				query_list.buff_up(true, true);

				if (query_list.get_itr() == query_list.size()) query_list.set_itr(0);
			}

			else if (tab_process) {
				tab_process = false;
				query_list.set_itr(0);
			}

			itelli_stdin_arrow_config(ch, buffer, it_buff, index, col);

			std::cout << os::load_c() << os::del_win(0);

			for (size_t i = 0; i < buffer.size(); i++)
			{
				switch ((int)buffer[i])
				{
				case is::Quote: {
					size_t init_index = i;
					for (i; i < buffer.size(); i++) {
						if (i == index && draw_caret) itelli_draw_caret(defs.caret_color, buffer[i]);
						else std::cout << os::clr(util::str_char(buffer[i]), defs.quote_color);
						if ((int)buffer[i] == is::Quote && i != init_index) break;
					}
					continue;
				}

				//         '#'
				case is::NumberSign:
					if (buffer[i + 1] == '(') {
						size_t end = util::find_first(buffer, ')', i);

						if (end >= buffer.size()) end--;

						for (i; i <= end; i++) {
							if (i == index && draw_caret) itelli_draw_caret(defs.caret_color, buffer[i]);
							else std::cout << os::clr(util::str_char(buffer[i]), defs.number_sign_color);
						}

						i--;
						continue;
					}

					else {
						for (i; i < buffer.size(); i++) {
							if (buffer[i] == ' ') break;
							if (i == index && draw_caret) itelli_draw_caret(defs.caret_color, buffer[i]);
							else std::cout << os::clr(util::str_char(buffer[i]), defs.number_sign_color);
						}
					}
					break;
				
				case is::DollarSign: {
					std::string name = "";

					for (size_t o = i + 1; o < buffer.size(); o++) {
						if (buffer[o] == ' ') break;
						name += buffer[o];
					}

					for (i; i < buffer.size(); i++) {
						if (buffer[i] == ' ') break;
						if (i == index && draw_caret) itelli_draw_caret(defs.caret_color, buffer[i]);
						else if (dbase.exist_shortcut(name)) std::cout << os::clr(util::str_char(buffer[i]), defs.dollar_sign_color);
						else std::cout << buffer[i];
					}
					break;
				}

				case is::Hyphen:
					for (i; i < buffer.size(); i++) {
						if (buffer[i] == ' ') break;
						if (i == index && draw_caret) itelli_draw_caret(defs.caret_color, buffer[i]);
						else std::cout << os::clr(util::str_char(buffer[i]), defs.hyphen_color);
					}
					break;

				case is::Backslash: {
					std::string full;
					std::string color = "Null";
					std::string mode = "NORMAL";
					std::vector<std::string> s_full;

					for (size_t o = i + 1; o < buffer.size(); o++) {
						if (buffer[o] == ' ') break;
						full += buffer[o];
					}

					s_full = util::split_string(full, ';');

					if (s_full.size() >= 1) color = util::to_upper(s_full[0]);
					if (s_full.size() >= 2) mode = util::to_upper(s_full[1]);

					for (i; i < buffer.size(); i++) {
						if (buffer[i] == ' ') break;
						if (i == index && draw_caret) itelli_draw_caret(defs.caret_color, buffer[i]);
						else if (util::string_to_color(color) != os::Nothing) std::cout << os::clr(util::str_char(buffer[i]), util::string_to_color(color), util::string_to_color_mode(mode));
						else std::cout << buffer[i];
					}
					break;
				}

				case is::LeftCurlyBrace: {
					size_t end = util::find_first(buffer, '}', i);

					if (end >= buffer.size()) end--;

					for (i; i <= end; i++) {
						if (i == index && draw_caret) itelli_draw_caret(defs.caret_color, buffer[i]);
						else std::cout << os::clr(util::str_char(buffer[i]), defs.curly_brace_color);
					}

					i--;
					continue;
				}
				}				


				if ((cmd::check(util::split_string(buffer)[0]) != cmd::Not_found || dbase.exist_function(util::split_string(buffer)[0])) && i < util::find_first(buffer, ' '))
					for (i; i < util::find_first(buffer, ' '); i++) {
						if (i >= buffer.size()) break;
						if (i == index && draw_caret) itelli_draw_caret(defs.caret_color, buffer[i]);
						else std::cout << os::clr(util::str_char(buffer[i]), defs.command_color);
					}

				if (op::check(buffer[0]) != op::Null)
					for (i; i < util::find_first(buffer, ' '); i++) {
						if (i >= buffer.size()) break;
						if (i == index && draw_caret) itelli_draw_caret(defs.caret_color, buffer[i]);
						else std::cout << os::clr(util::str_char(buffer[i]), os::PURPLE);
					}

				if (i == index && draw_caret) itelli_draw_caret(defs.caret_color, buffer[i]);
				else std::cout << buffer[i];
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
		else if (ch != is::Enter && ch != is::Tab) {
			buffer = util::insert(buffer, util::str_char(ch), index);
			index++;
		}
	}
}