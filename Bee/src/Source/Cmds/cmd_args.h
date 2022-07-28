#pragma once

#include "../Util/string_util.h"

#include <string>
#include <vector>

namespace cmd
{
	enum ArgType
	{
		Argument,
		Flag
	};


	class Arg
	{
	public:
		Arg(std::string arg)
		{
			this->arg = arg;
			this->type = (this->arg[0] == '-') ? Flag : Argument;
		};

		inline std::string get_arg() { return this->arg; }
		inline ArgType get_type() { return this->type; }

		inline std::string get_flag() { return (this->type == Flag) ? util::erase_first(this->arg) : ""; }

	private:
		std::string arg;
		ArgType type;
	};


	class CMD_Arg
	{
	public:
		CMD_Arg() {};
		CMD_Arg(std::vector<std::string> args) 
		{
			for (std::string arg : args)
				this->args.push_back(Arg(arg));
		}

		inline void operator=(std::vector<std::string> args) 
		{
			this->args = std::vector<Arg>({});

			for (std::string arg : args)
				this->args.push_back(Arg(arg));
		}

		inline Arg operator[](size_t index) { return this->args[index]; }

		inline std::vector<Arg> get() { return this->args; }

	private:
		std::vector<Arg> args;
	};
}