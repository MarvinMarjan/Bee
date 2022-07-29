#pragma once

#include <string>
#include <vector>

namespace dt
{
	class Shortcut
	{
	public:
		Shortcut(std::string name, std::string value)
		{
			this->name = name;
			this->value = value;
		}

		inline void operator=(std::string value) { this->value = value; }

		inline std::string get_name() { return this->name; }
		inline std::string get_value() { return this->value; }

		inline void set_value(std::string value) { this->value = value; }

	private:
		std::string name;
		std::string value;
	};
}