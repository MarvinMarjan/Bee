#pragma once

#include <string>
#include <vector>

namespace dt
{
	class Shortcut
	{
	public:
		friend class DBase;

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
		Shortcut(std::string name, std::string value, bool predef)
		{
			this->name = name;
			this->value = value;
			this->predef = predef;
		}

		std::string name;
		std::string value;

		bool predef = false;
	};
}