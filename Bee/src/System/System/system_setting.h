#pragma once

#include <string>

namespace sys
{
	class Sys_Setting
	{
	public:
		Sys_Setting(std::string name, std::string value) {
			this->name = name;
			this->value = value;
		}

		inline void set_value(std::string value) { this->value = value; }

		inline std::string get_value() { return this->value; }
		inline std::string get_name() { return this->name; }

	private:
		std::string name;
		std::string value;
	};
}