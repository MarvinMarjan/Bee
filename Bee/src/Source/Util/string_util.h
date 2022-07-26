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
}