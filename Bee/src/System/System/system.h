#pragma once

#include <iostream>

#include "../../Source/Stream/ostream_clr.h"
#include "../../Source/Cmds/commands.h"

#include "system_err.h"
#include "system_warn.h"


#define VERSION "0.0.4.1"
#define VERSION_STATE "DEV - TEST"
#define NAME "Bee"


namespace sys
{
	class System
	{
	public:
		bool abort = false;
		bool blocked = false;
		bool cmd_blocked = false;
	};

	inline void error(sys::Error err, std::string arg = "") 
	{
		std::cout << os::clr("[" + err.name + "] ", os::WT_RED) << err.msg;

		if (arg != "")
			std::cout << ": " << os::clr('\"' + arg + '\"', os::GREEN);

		std::cout << std::endl << std::endl;
	}

	inline void warn(sys::Warning warn, std::string arg = "")
	{
		std::cout << os::clr("[" + warn.name + "] ", os::WT_YELLOW) << warn.msg;

		if (arg != "")
			std::cout << ": " << os::clr('\"' + arg + '\"', os::GREEN);

		std::cout << std::endl << std::endl;
	}

	inline void details()
	{
		std::cout << os::clr("Name: ", os::WT_YELLOW) << os::clr(NAME, os::YELLOW) << std::endl <<
			os::clr("Version: ", os::WT_YELLOW) << os::clr(VERSION, os::WT_GREEN) << " " << os::clr(VERSION_STATE, os::PURPLE, os::UNDERLINE) << std::endl << std::endl;
	}

	inline void help(cmd::CMD_Data cmd)
	{
		std::string names = "";

		for (size_t i = 0; i < cmd.name_variants.size(); i++)
			names += cmd.name_variants[i] + ((i + 1 >= cmd.name_variants.size()) ? "" : " | ");

		std::cout << os::clr(cmd.name, os::WT_CYAN) << " - " << os::clr(cmd.syntax, os::CYAN) << ((cmd.name_variants.size()) ? " -> " + os::clr(names, os::WT_YELLOW) : "") << std::endl << '\t' << cmd.description << std::endl << std::endl;
	}
}