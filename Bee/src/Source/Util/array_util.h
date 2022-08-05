#pragma once

#include <string>
#include <vector>

namespace util
{
	template<typename T>
	inline std::vector<T> get_from(std::vector<T> src, size_t index)
	{
		std::vector<T> _src;

		for (size_t i = index; i < src.size(); i++)
			_src.push_back(src[i]);

		return _src;
	}
}