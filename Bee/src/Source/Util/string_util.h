#pragma once

#include <string>
#include <vector>

namespace util
{
	std::vector<std::string> split_string(std::string src, char ch = ' ')
	{
		std::vector<std::string> split;
		std::string aux = "";

		for (size_t i = 0; i < src.size(); i++)
		{
			if (src[i] == ch || i + 1 >= src.size())
			{
				if (i + 1 >= src.size())
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

	inline std::string swap(std::string src, char targ_ch, char new_ch)
	{
		std::string s_src = "";

		for (size_t i = 0; i < src.size(); i++)
			s_src += ((src[i] == targ_ch) ? new_ch : src[i]);

		return s_src;
	}

	inline size_t find_first(std::string src, char ch)
	{
		for (size_t i = 0; i < src.size(); i++)
			if (src[i] == ch)
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

	inline size_t find_last(std::string src, char ch)
	{
		size_t index = -1;

		for (size_t i = 0; i < src.size(); i++)
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

		for (size_t i = 0; i < src.size(); i++)
			if (i != ch_index)
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

	inline bool ends_with(std::string src, char ch)
	{
		return (src.size() && src[src.size() - 1] == ch);
	}

	inline std::string to_lower(std::string src)
	{
		std::string l_src;

		for (char ch : src) l_src += tolower(ch);

		return l_src;
	}
}