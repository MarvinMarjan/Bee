#pragma once

#include "system.h"

namespace sys
{
	enum CommandType
	{
		Null,
		
		All,
		Base,
		Instruction
	};

	inline bool is_cmd_same_type(cmd::CMD_Data cmd, CommandType type)
	{
		switch (type)
		{
		case All: return true;
		case Base: return cmd.predef;
		case Instruction: return cmd.instruction;
		default: return Null;
		}
	}
	
	inline void help(cmd::CMD_Data cmd)
	{
		std::string names = "";

		for (size_t i = 0; i < cmd.name_variants.size(); i++)
			names += cmd.name_variants[i] + ((i + 1 >= cmd.name_variants.size()) ? "" : " | ");

		std::cout << os::clr(cmd.name, ((cmd.predef) ? os::YELLOW : (cmd.instruction) ? os::PURPLE : os::WT_CYAN)) << " - " << os::clr(cmd.syntax, os::CYAN) << ((cmd.name_variants.size()) ? " -> " + os::clr(names, os::WT_YELLOW) : "") << std::endl << '\t' << cmd.description << std::endl << std::endl;
	}

	inline void only_name_help(CommandType cmd_type = All)
	{
		std::vector<cmd::CMD_Data> _commands = util::filter<cmd::CMD_Data, CommandType>(cmd::commands, 
			[] (cmd::CMD_Data cmd, CommandType type) { return is_cmd_same_type(cmd, type); }, cmd_type);

		for (size_t i = 0; i < _commands.size(); i += 2)
			if (is_cmd_same_type(_commands[i], cmd_type)) std::cout << std::setw(40) << std::left << os::clr(_commands[i].name, ((_commands[i].predef) ? os::YELLOW : (_commands[i].instruction) ? os::PURPLE : os::WT_CYAN))
			<< std::right << ((i + 1 >= _commands.size()) ? "" : os::clr(_commands[i + 1].name, ((_commands[i + 1].predef) ? os::YELLOW : (_commands[i + 1].instruction) ? os::PURPLE : os::WT_CYAN))) << std::endl;

	}
}