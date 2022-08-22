#pragma once

#include <Windows.h>
#include <iostream>

#include "../../Source/Stream/ostream_snippet.h"
#include "../../Source/Stream/ostream_clr.h"
#include "../../Source/Cmds/commands.h"

#include "system_warn.h"
#include "system_ask.h"
#include "system_err.h"


#define VERSION "0.0.7.0"
#define VERSION_STATE "DEV - TEST"
#define NAME "Bee"


namespace sys
{
	class System
	{
	public:
		bool abort = false;

		bool use_itellisense = true;

		size_t inline_mode_arg_itr = 0;
		size_t readfile_mode_arg_itr = 0;

		size_t mode_arg_index;

		inline void update(System_Settings sys_config)
		{
			if (boolstring_to_bool(sys_config["itellisense"]->get_value()))
				this->use_itellisense = true;
			else 
				this->use_itellisense = false;
		}

		~System() {
			util::set_mouse_visible(util::True);
		}
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

	inline bool ask(sys::Question ask)
	{
		util::set_mouse_visible(util::True);
		std::string res;
		std::cout << os::clr("[" + ask.name + "] ", os::WT_GREEN) << ask.msg << " (S/N): ";

		std::getline(std::cin, res);
		res = util::to_lower(res);

		if (res == "y" || res == "yes") return true;
		if (res == "n" || res == "no") return false;

		util::set_mouse_visible(util::False);
		return false;
	}

	inline void details()
	{
		std::cout << os::clr("Name: ", os::WT_YELLOW) << os::clr(NAME, os::YELLOW) << std::endl <<
			os::clr("Version: ", os::WT_YELLOW) << os::clr(VERSION, os::WT_GREEN) << " " << os::clr(VERSION_STATE, os::PURPLE, os::UNDERLINE) << std::endl << std::endl;
	}

	inline void OS_stat(MEMORYSTATUSEX stat, bool update = false)
	{
		std::cout << "Physical     RAM (MB): " << os::clr(std::to_string(stat.ullTotalPhys/1024/1024), os::Color::WT_CYAN) << std::endl;

		std::cout << "Avaliable    RAM (KB): " << os::clr(std::to_string(stat.ullAvailPhys/1024), os::Color::WT_CYAN) << std::endl;
		std::cout << "RAM Usage            : " << os::clr(std::to_string(stat.dwMemoryLoad) + '%', os::Color::WT_CYAN) << std::endl;
	
		if (update)
		{
			for (size_t i = 0; i < 500000000; i++) {}

			std::cout << os::up_ln() << os::del_ln(2) << os::up_ln() << os::del_ln(2) << os::up_ln() << os::del_ln(2);
		}
	}

	inline void bee_help()
	{

	}

	inline void help(cmd::CMD_Data cmd)
	{
		std::string names = "";

		for (size_t i = 0; i < cmd.name_variants.size(); i++)
			names += cmd.name_variants[i] + ((i + 1 >= cmd.name_variants.size()) ? "" : " | ");

		std::cout << os::clr(cmd.name, os::WT_CYAN) << " - " << os::clr(cmd.syntax, os::CYAN) << ((cmd.name_variants.size()) ? " -> " + os::clr(names, os::WT_YELLOW) : "") << std::endl << '\t' << cmd.description << std::endl << std::endl;
	}
}