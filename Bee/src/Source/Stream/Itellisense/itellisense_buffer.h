#pragma once

#include "../istream.h"

#include <string>
#include <vector>

namespace it
{
	class Itelli_Buffer
	{
	public:
		inline is::Buffer operator[](size_t index) { return this->buff[index]; }

		inline void add_buff(is::Buffer buff) { this->buff.push_back(buff); }

		inline is::Buffer buff_get() { return this->buff[this->iterator]; }

		inline void buff_up() { this->iterator++; }
		inline void buff_dw() { this->iterator--; }

	private:
		size_t iterator = 0;

		std::vector<is::Buffer> buff;
	};
}