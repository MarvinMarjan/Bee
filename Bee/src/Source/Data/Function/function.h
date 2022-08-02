#pragma once

#include <string>
#include <vector>

namespace dt
{
	class Function
	{
	public:
		Function() {};
		Function(std::string name, std::vector<std::string> block)
		{
			this->name = name;
			this->block = block;
		}

		inline std::string get_name() { return this->name; }
		inline std::vector<std::string> get_block() { return this->block; }

	private:
		std::string name;
		std::vector<std::string> block;
	};
}