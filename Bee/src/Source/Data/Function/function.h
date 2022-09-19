#pragma once

#include <string>
#include <vector>

namespace dt
{
	class Function
	{
	public:
		friend class DBase;

		Function() {};

		Function(std::string name, std::vector<std::string> block) {
			this->name = name;
			this->block = block;
		}

		Function(std::string name, std::vector<std::string> block, std::string return_value) {
			this->name = name;
			this->block = block;
			this->return_value = return_value;
		}

		inline std::string get_name() { return this->name; }
		inline std::vector<std::string> get_block() { return this->block; }
		inline std::string get_return_value() { return this->return_value; }

		inline void set_block(std::vector<std::string> block) { this->block = block; }
		inline void set_return_value(std::string return_value = "") { this->return_value = return_value; }

		inline void operator=(std::vector<std::string> block) { this->set_block(block); }

	private:
		Function(std::string name, std::vector<std::string> block, bool predef) {
			this->name = name;
			this->block = block;
			this->predef = predef;
		}

		std::string name;
		std::vector<std::string> block;
		std::string return_value = "";

		bool predef = false;
	};
}