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

		inline size_t size() { return this->buff.size(); }

		inline void add_buff(is::Buffer buff) { 
			this->buff.push_back(buff); 
			this->iterator = this->buff.size() - 1;
		}

		inline is::Buffer buff_get() { return this->buff[this->iterator]; }

		inline void buff_up() { 
			if (this->iterator + 1 < this->buff.size()) {
				if (!this->init) this->iterator++;
				else this->init = false;
			}
		}

		inline void buff_dw() {
			if (this->iterator > 0) {
				if (!this->init) this->iterator--;
				else this->init = false;
			}
		}

	private:
		size_t iterator = 0;
		bool init = true;

		std::vector<is::Buffer> buff;
	};
}