#pragma once

#include <string>
#include <vector>

namespace util
{
	std::vector<std::string> format_args(std::vector<std::string> src)
	{
		std::vector<std::string> f_src;

		for (size_t i = 1; i < src.size(); i++)
		{
			if (src[i][0] == '\"')
			{
				std::string aux = "";

				for (i; i < src.size(); i++)
				{
					aux += src[i] + ((src[i][src[i].size() - 1] == '\"') ? "" : " ");

					if (src[i][src[i].size() - 1] == '\"')
						break;
				}

				aux.erase(0, 1);
				aux.erase(aux.size() - 1);

				f_src.push_back(aux);
			}

			else
				f_src.push_back(src[i]);
		}

		return f_src;
	}
}