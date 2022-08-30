#pragma once

#include <Windows.h>
#include <iostream>

#include "../../Deps/nlohmann/json.hpp"

#include "../../Source/Stream/ostream_snippet.h"
#include "../../Source/Stream/ostream_clr.h"
#include "../../Source/Cmds/commands.h"

#include "../../Source/Util/filesys_util.h"

#include "system_warn.h"
#include "system_ask.h"
#include "system_err.h"

#define BEE_OPERATIONAL_SYSTEM "Windows"
#define BEE_VERSION_STATE "DEV - TEST"
#define BEE_VERSION "v0.0.8.2"
#define BEE_NAME "Bee"

using json = nlohmann::json;

namespace sys
{
	const std::vector<Error> errs =
	{
		Error(Function_Not_Found_Err),
		Error(Shortcut_Not_Found_Err),
		Error(Setting_Not_Found_Err),
		Error(Command_Not_Found),

		Error(Invalid_Path_File),
		Error(Invalid_Path_Dir)
	};

	const std::vector<Warning> warns =
	{
		Warning(DataBase_Bootstrap_Err),
		Warning(Settings_Bootstrap_Err),

		Warning(Incomplete_Expression),
		Warning(Shortcut_Not_Found_Warn),
		Warning(Insufficient_Args)
	};


	class System
	{
	public:
		bool use_itellisense = true;
		bool pause_sys = false;
		bool abort = false;

		bool disable_errs_msg = false;
		bool disable_warns_msg = false;

		size_t inline_mode_arg_itr = 0;
		size_t readfile_mode_arg_itr = 0;
		size_t mode_arg_index;

		std::string version_state;
		std::string version;
		std::string name;
		std::string os;

		System() {
			this->os = BEE_OPERATIONAL_SYSTEM;
			this->name = BEE_NAME;
			this->version = BEE_VERSION;
			this->version_state = BEE_VERSION_STATE;
		}

		~System() {
			util::set_mouse_visible(util::True);
		}
		
		inline void update(System_Settings& sys_config)
		{
			this->use_itellisense = boolstring_to_bool(sys_config["itellisense"]->get_value());
			this->disable_errs_msg = boolstring_to_bool(sys_config["disable_error_msg"]->get_value());
			this->disable_warns_msg = boolstring_to_bool(sys_config["disable_warn_msg"]->get_value());
		}

		inline void error(sys::Error err, std::string arg = "")
		{
			if (this->disable_errs_msg) return;

			std::cout << os::clr("[" + err.name + "] ", os::WT_RED) << err.msg;

			if (arg != "")
				std::cout << ": " << os::clr('\"' + arg + '\"', os::GREEN);

			std::cout << std::endl << std::endl;
		}

		inline void warn(sys::Warning warn, std::string arg = "")
		{
			if (this->disable_warns_msg) return;

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
	};

	inline void details(System& system)
	{
		std::cout << os::clr("name: ", os::WT_YELLOW) << os::clr(system.name, os::YELLOW) << std::endl;
		std::cout << os::clr("version: ", os::WT_YELLOW) << os::clr(system.version, os::WT_GREEN) 
			<< " " << os::clr(system.version_state, os::PURPLE, os::UNDERLINE) << std::endl;
		
		std::cout << os::clr("os: ", os::WT_YELLOW) << os::clr(system.os, os::WT_CYAN) << std::endl << std::endl;
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