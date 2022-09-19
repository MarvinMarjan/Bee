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
	inline T concat(T arr1, T arr2)
	{
		T _arr;

		for (size_t i = 0; i < arr1.size(); i++)
			_arr.push_back(arr1[i]);

		for (size_t i = 0; i < arr2.size(); i++)
			_arr.push_back(arr2[i]);

		return _arr;
	}

	template<typename T>
	inline void print(std::vector<T> arr, char spliter = '\n')
	{
		for (size_t i = 0; i < arr.size(); i++)
			std::cout << arr[i] << spliter;
	}

	template<typename T>
	inline std::vector<T> filter(std::vector<T> arr, bool (*func)(T))
	{
		std::vector<T> filtered;

		for (size_t i = 0; i < arr.size(); i++)
			if (func(arr[i])) filtered.push_back(arr[i]);

		return filtered;
	}

	template<typename T1, typename T2>
	inline std::vector<T1> filter(std::vector<T1> arr, bool (*func)(T1, T2), T2 callback_argument)
	{
		std::vector<T1> filtered;

		for (size_t i = 0; i < arr.size(); i++)
			if (func(arr[i], callback_argument)) filtered.push_back(arr[i]);

		return filtered;
	}

	template<typename T1, typename T2>
	inline std::vector<T2> map(std::vector<T1> arr, T2 (*func)(T1))
	{
		std::vector<T2> mapped;

		for (size_t i = 0; i < arr.size(); i++)
			mapped.push_back(func(arr[i]));

		return mapped;
	}

	template<typename T>
	inline void foreach(std::vector<T> arr, void (*func)(T)) {
		for (size_t i = 0; i < arr.size(); i++) func(arr[i]);
	}
}