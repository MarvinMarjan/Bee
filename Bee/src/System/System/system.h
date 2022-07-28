#pragma once

#include <iostream>

#include "../../Source/Stream/ostream_clr.h"
#include "../../Source/Cmds/commands.h"

#include "system_err.h"
#include "system_warn.h"


#define VERSION "0.0.0"
#define VERSION_STATE "DEV"
#define NAME "Bee"


namespace sys
{
	class System
	{
	public:
		bool abort = false;
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
		std::cout << "Name: " << os::clr(NAME, os::YELLOW) << std::endl << 
			"Version: " << VERSION << " " << os::clr(VERSION_STATE, os::PURPLE, os::UNDERLINE) << std::endl << std::endl;
	}

	inline void help(cmd::CMD_Data cmd)
	{
		std::cout << os::clr(cmd.name, os::WT_CYAN) << " - " << os::clr(cmd.syntax, os::CYAN) << std::endl << '\t' << cmd.description << std::endl << std::endl;
	}
}