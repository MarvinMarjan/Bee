#pragma once

#include <iostream>

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

	template<typename T>
	inline std::vector<T> get_between(std::vector<T> src, size_t begin, size_t end)
	{
		std::vector<T> _src;

		for (size_t i = begin; i < end; i++)
			_src.push_back(src[i]);

		return _src;
	}

	template<typename T>
	inline bool exist(T item, std::vector<T> arr)
	{
		for (size_t i = 0; i < arr.size(); i++)
			if (item == arr[i]) 
				return true;

		return false;
	}

	template<typename T>
	inline void print(std::vector<T> arr, char spliter = '\n')
	{
		for (size_t i = 0; i < arr.size(); i++)
			std::cout << arr[i] << spliter;
	}
}