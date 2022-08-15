#pragma once

#include "../Util/string_util.h"

#include <string>
#include <conio.h>

namespace is
{
	class Buffer
	{
	public:
		Buffer(std::string buff) { this->buff = buff; }
		Buffer() { this->buff = ""; }

		inline void operator+=(char ch) { this->buff += ch; }
		inline void operator+=(std::string ch) { this->buff += ch; }

		inline void operator=(std::string buff) { this->buff = buff; }

		inline bool operator==(std::string other) { return (this->buff == other); }
		inline bool operator!=(std::string other) { return (this->buff != other); }

		inline char operator[](size_t index) { return this->buff[index]; }

		inline std::string get() { return this->buff; }
		inline std::vector<std::string> get_split() { return util::split_string(this->buff); }

		inline size_t size() { return this->buff.size(); }

		inline void erase_last()
		{
			std::string buff = "";

			for (size_t i = 0; i < this->size() - 1; i++)
				buff += this->buff[i];

			this->buff = buff;
		}

	private:
		std::string buff;
	};

	enum CharCode
	{
		Backspace = 8,
		Enter = 13,

		Arrow = -32,

		ArrowUp = 72,
		ArrowDown = 80,
		ArrowLeft = 75,
		ArrowRight = 77,

		Quote = 34,
		DollarSign = 36,
		Hyphen = 45,

		Tab = 9
	};

	inline char get_ch() { return _getch();	}

	inline bool k_hit() { return _kbhit(); }

	inline std::string get_line()
	{
		std::string buff;
		std::getline(std::cin, buff);

		return buff;
	}
}