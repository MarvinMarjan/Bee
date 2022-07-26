#pragma once

#include <string>
#include <vector>

namespace util
{
	enum Direction
	{
		Left,
		Right
	};

	inline std::string erase_last(std::string src);

	std::vector<std::string> split_string(std::string src, char ch = ' ')
	{
		std::vector<std::string> split;
		std::string aux = "";

		for (size_t i = 0; i < src.size(); i++)
		{
			if (src[i] == ch || i + 1 >= src.size())
			{
				if (i + 1 >= src.size() && src[src.size() - 1] != ch)
					aux += src[i];

				split.push_back(aux);
				aux = "";
				continue;
			}

			aux += src[i];
		}

		return split;
	}

	std::string join_string(std::vector<std::string> src, std::string ch = " ", size_t init = 0)
	{
		std::string j_src = "";

		for (size_t i = init; i < src.size(); i++)
			j_src += src[i] + ((i + 1 >= src.size()) ? "" : ch);
		
		return j_src;
	}

	std::string sub_string(std::string src, size_t begin, size_t end)
	{
		std::string substr = "";

		for (size_t i = begin; i < end; i++)
		{
			substr += src[i];
			if (i + 1 >= src.size()) break;
		}

		return substr;
	}

	inline std::string swap(std::string src, char targ_ch, char new_ch)
	{
		std::string s_src = "";

		for (size_t i = 0; i < src.size(); i++)
			s_src += ((src[i] == targ_ch) ? new_ch : src[i]);

		return s_src;
	}

	size_t find_first(std::string src, char ch, size_t init = 0, Direction direction = Right)
	{
		size_t i = init;

		for (i; ; ((direction == Right) ? i++ : i--)) {
			if (src[i] == ch)
				return i;

			if (direction == Right && i >= src.size()) break;
			if (direction == Left && i <= 0) break;
		}

		return i;
	}

	inline std::vector<size_t> find_all(std::string src, char ch)
	{
		std::vector<size_t> indexes;

		for (size_t i = 0; i < src.size(); i++)
			if (src[i] == ch)
				indexes.push_back(i);

		return indexes;
	}

	size_t find_last(std::string src, char ch, size_t init = 0, Direction direction = Right)
	{
		size_t index = -1;

		for (size_t i = init; ((direction == Right) ? i < src.size() : i >= 0); ((direction == Right) ? i++ : i--))
			if (src[i] == ch)
				index = i;

		return index;
	}

	inline std::string erase(std::string src, size_t begin, size_t end = -1)
	{
		std::string e_src = "";

		if (end == -1)
			end = src.size();

		for (size_t i = 0; i < src.size(); i++)
			if (i < begin || i > end)
				e_src += src[i];

		return e_src;
	}

	inline std::string erase_ch(std::string src, size_t ch_index)
	{
		std::string e_src = "";

		if (ch_index == src.size()) return util::erase_last(src);

		for (size_t i = 0; i < src.size(); i++)
			if (i != ch_index - 1)
				e_src += src[i];

		return e_src;
	}

	inline std::string erase_last(std::string src)
	{
		std::string e_src = "";

		if (src.size() != 0)
			for (size_t i = 0; i < src.size() - 1; i++)
				e_src += src[i];

		return e_src;
	}

	inline std::string erase_first(std::string src, size_t count = 1)
	{
		std::string e_src = "";

		count = ((count < 1) ? 1 : count);
		for (size_t i = count; i < src.size(); i++)
			e_src += src[i];

		return e_src;
	}

	inline bool starts_with(std::string src, std::string str)
	{
		for (size_t i = 0; i < str.size(); i++)
			if (src[i] != str[i])
				return false;

		return true;
	}

	inline bool ends_with(std::string src, char ch) {
		return (src.size() && src[src.size() - 1] == ch);
	}

	inline std::string to_lower(std::string src) {
		std::string l_src;
		for (char ch : src) l_src += tolower(ch);
		return l_src;
	}

	inline std::string to_upper(std::string src) {
		std::string u_src;
		for (char ch : src) u_src += toupper(ch);
		return u_src;
	}
	
	inline std::string insert(std::string src, std::string str, size_t index)
	{
		std::string n_src = "";

		if (index >= src.size()) return src + str;

		for (size_t i = 0; i < src.size(); i++)
		{
			if (i == index) n_src += str;
			n_src += src[i];
		}

		return n_src;
	}

	inline std::string str_char(char ch) {
		std::string str(1, ch);
		return str;
	}

	inline std::string bool_to_str(bool src) {
		if (src) return "true";
		else return "false";
	}
	
	inline bool str_to_bool(std::string src) {
		if (src == "true") return true;
		else return false;
	}

	inline std::string get_until(std::string src, char ch, size_t index = 0, Direction direction = Right)
	{
		std::string _src = "";

		for (index; ((direction == Right) ? index < src.size() : index >= 0); ((direction == Right) ? index++ : index--)) {
			if (src[index] == ch) return _src;
			_src += src[index];
		}

		return _src;
	}

	inline bool exist_ch(std::string src, char ch)
	{
		for (char _ch : src)
			if (_ch == ch)
				return true;

		return false;
	}
}