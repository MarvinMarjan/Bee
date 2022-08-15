#pragma once

#include <string>
#include <vector>

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
}