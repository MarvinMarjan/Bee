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
		
		inline void operator=(std::vector<std::string> buffs) { this->set_buff(buffs); }
		inline void operator=(std::vector<is::Buffer> buffs) { this->buff = buff; }

		inline size_t size() { return this->buff.size(); }

		inline void set_buff(std::vector<is::Buffer> buff, bool reset_itr = true) {
			this->buff = buff;
			if (reset_itr) this->set_itr();
		}
		inline void set_buff(std::vector<std::string> buff, bool reset_itr = true) {
			this->buff.clear();
			for (std::string str : buff)
				this->buff.push_back(is::Buffer(str));
			if (reset_itr) this->set_itr();
		}

		inline void add_buff(is::Buffer buff, bool reset_itr = true) { 
			this->buff.push_back(buff); 
			if (reset_itr) this->set_itr();
		}

		inline is::Buffer buff_get() { return this->buff[this->iterator]; }

		inline is::Buffer buff_get_last() { return this->buff[this->iterator - ((this->iterator > 0) ? 1 : 0)]; }
		inline is::Buffer buff_get_next() { return this->buff[this->iterator + ((this->iterator < this->size()) ? 1 : 0)]; }

		inline void buff_up(bool ignore_init = false, bool ignore_limit = false) { 
			if (this->iterator + 1 < this->buff.size() || ignore_limit) {
				if (!this->init || ignore_init) this->iterator++;
				this->init = false;
			}
		}

		inline void buff_dw(bool ignore_init = false, bool ignore_limit = false) {
			if (this->iterator > 0 || ignore_limit) {
				if (!this->init || ignore_init) this->iterator--;
				this->init = false;
			}
		}

		inline size_t get_itr() { return this->iterator; }
		inline void set_itr(size_t itr) { this->iterator = itr; }

		inline size_t get_size() { return this->buff.size(); }

	private:
		inline void set_itr() { this->iterator = this->buff.size() - 1; }

		size_t iterator = 0;
		bool init = true;

		std::vector<is::Buffer> buff;
	};
}