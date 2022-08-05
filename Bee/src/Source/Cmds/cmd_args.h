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

		inline std::string get_arg(bool ignore = true) { return (this->type == Flag && ignore) ? "" : this->arg; }
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
		inline std::vector<std::string> get_str(bool ignore = true) 
		{
			std::vector<std::string> str_args;

			for (Arg arg : this->args)
				str_args.push_back(arg.get_arg(ignore));

			return str_args;
		}

		inline void erase_first()
		{
			std::vector<Arg> e_args;

			for (size_t i = 1; i < this->args.size(); i++)
				e_args.push_back(this->args[i]);

			this->args = e_args;
		}

		inline void erase_flags()
		{
			for (size_t i = 0; i < this->args.size(); i++)
				if (this->args[i].get_type() == cmd::Flag)
				{
					this->args.erase(this->args.begin() + i);
					i--;
				}
		}

	private:
		std::vector<Arg> args;
	};
}