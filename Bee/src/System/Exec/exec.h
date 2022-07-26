#pragma once

#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>
#include <vector>

#include "../../Deps/nlohmann/json.hpp"

#include "../../System/Handle/path_handling.h"

#include "../../System/Bootstrap/bootstrap_flag.h"
#include "../../System/Bootstrap/bootstrap_mode.h"
#include "../../System/Bootstrap/bootstrap.h"

#include "../../System/System/System_Settings/setting_types_converts.h"
#include "../../System/System/System_Settings/system_setting_def.h"
#include "../../System/System/System_Settings/system_setting.h"
#include "../../System/System/system_help.h"
#include "../../System/System/system_warn.h"
#include "../../System/System/system_ask.h"
#include "../../System/System/system_err.h"
#include "../../System/System/system.h"

#include "../../Source/Stream/Itellisense/itellisense_buffer.h"
#include "../../Source/Stream/Itellisense/itellisense.h"
#include "../../Source/Stream/ostream_snippet.h"
#include "../../Source/Stream/ostream_clr.h"
#include "../../Source/Stream/istream.h"

#include "../../Source/Data/Shortcut/shortcut.h"
#include "../../Source/Data/data.h"

#include "../../Source/Cmds/Diagnostic/diag_data.h"
#include "../../Source/Cmds/commands.h"
#include "../../Source/Cmds/cmd_args.h"
#include "../../Source/Cmds/cmd_data.h"
#include "../../Source/Cmds/cmd_flag.h"

#include "../../Source/Operator/operator.h"

#include "../../Source/Util/filesys_util.h"
#include "../../Source/Util/system_util.h"
#include "../../Source/Util/memory_util.h"
#include "../../Source/Util/string_util.h"
#include "../../Source/Util/array_util.h"
#include "../../Source/Util/exec_util.h"
#include "../../Source/Util/cmd_util.h"

bool can_use_else_statement = false;

void run(sys::System& system, sys::System_Settings& sys_config, sys::Defs& defs, hand::Path& path, dt::DBase& dbase, is::Buffer& buff, 
	     std::vector<std::string> s_buff, cmd::CMD_Arg& args, cmd::CMD_Flags& flags, dt::Function* parent_func)
{
	if (dbase.exist_function(s_buff[0]) && !dbase.is_predef_function(s_buff[0]))
	{
		dt::Function* function = dbase.get_function(s_buff[0]);
		size_t args_count = 1;

		for (args_count; args_count <= args.get().size(); args_count++)
			dbase.add_shortcut(dt::Shortcut(("arg" + std::to_string(args_count)), args[args_count - 1].get_arg()));

		for (std::string line : function->get_block()) {
			buff = line;
			s_buff = ((buff.get_split().size() == 0) ? std::vector<std::string>({ "" }) : buff.get_split());
			args = util::format_args_all(system, sys_config, defs, path, parent_func, s_buff, dbase);

			flags = cmd::check_flags(args);
			args.erase_flags();

			run(system, sys_config, defs, path, dbase, buff, s_buff, args, flags, function);

		}
		
		for (size_t i = 1; i <= args_count; i++)
			dbase.del_shortcut(("arg" + std::to_string(i)));

		return;
	}

	switch (cmd::check(s_buff[0]))
	{
	case cmd::Null: break;
	case cmd::Exit:
		system.abort = true;
		break;

	case cmd::Setting: {
		if (args.get().size() == 0)
		{
			std::string name, value;
			sys::SettingType type;

			for (size_t i = 0; i < sys_config.get_size(); i++)
			{
				name = sys_config[i]->get_name();
				value = sys_config[i]->get_value();
				type = sys_config[i]->get_type();

				std::cout << std::setw(50) << std::left << os::clr('.' + std::to_string(i), os::WT_YELLOW) + "  " + os::clr(name, os::WT_CYAN);

				switch (type)
				{
				case sys::Color:
					std::cout << std::right << os::clr(value, util::semi_raw_to_color_set(value)) << std::endl;
					break;

				case sys::String:
					std::cout << std::right << os::clr('\"' + value + '\"', os::WT_GREEN) << std::endl;
					break;

				case sys::Bool:
					std::cout << std::right << os::clr(value, os::WT_YELLOW) << std::endl;
					break;
				}
			}
			break;
		}

		else if (args.get().size() == 1)
		{
			bool abort = false;
			std::string name = args[0].get_arg();
			std::string value;

			sys::SettingType type;

			if (name[0] == '.') {
				try {
					if (sys_config.exist((size_t)std::stoi(util::sub_string(name, 1, name.size()))))
						name = sys_config[(size_t)std::stoi(util::sub_string(name, 1, name.size()))]->get_name();
				}
				catch (...) {
					system.error(sys::Type_Conversion_Err, name);
					abort = true;
				}
			}

			if (!sys_config.exist(name) && !abort) system.error(sys::Setting_Not_Found_Err, name);
			else if (!abort) {
				type = sys_config[name]->get_type();
				value = sys_config[name]->get_value();

				std::cout << ((type == sys::Color) ? os::clr(value, util::semi_raw_to_color_set(value)) :
					(type == sys::Bool) ? os::clr(value, os::WT_YELLOW) : value) << std::endl;
			}
		}

		else if (args.get().size() == 2) {
			bool abort = false;
			std::string name = args[0].get_arg();
			std::string value;

			if (name[0] == '.') {
				try {
					if (sys_config.exist((size_t)std::stoi(util::sub_string(name, 1, name.size()))))
						name = sys_config[(size_t)std::stoi(util::sub_string(name, 1, name.size()))]->get_name();
				}
				catch (...) {
					system.error(sys::Type_Conversion_Err, name);
					abort = true;
				}
			}

			if (!sys_config.exist(name) && !abort) system.error(sys::Setting_Not_Found_Err, name);
			else if (!abort) {
				if (sys_config[name]->get_type() == sys::Color) {
					os::ColorSet color_set = util::raw_to_color_set(args[1].get_arg());

					value = '\\' + util::color_to_string(color_set.color) + ';' + util::color_mode_to_string(color_set.color_mode);
				}

				else value = (sys_config[name]->get_type() == sys::Bool) ? util::to_lower(args[1].get_arg()) : args[1].get_arg();
				if (sys_config[name]->is_same_type(value)) sys_config[name]->set_value(value);
			}
		}

		sys::set_defs(defs, sys_config);

		break;
	}

	case cmd::Get_Setting:
		if (util::_args(system, args, cmd::Get_Setting)) break;
		if (parent_func) {
			if (sys_config.exist(args[0].get_arg())) parent_func->set_return_value(sys_config[args[0].get_arg()]->get_value());
			else system.error(sys::Setting_Not_Found_Err, args[0].get_arg());
		}
		else std::cout << sys_config[args[0].get_arg()]->get_value() << std::endl;
		break;

	case cmd::Detail:
		sys::details(system);
		break;

	case cmd::Help:
		if (args.get().size() >= 1) {
			for (size_t i = 0; i < cmd::commands.size(); i++) {
				if (util::exist(args[0].get_arg(), cmd::commands[i].name_variants)) {
					sys::help(cmd::commands[i]);
					break;
				}
				if (i + 1 >= cmd::commands.size()) system.error(sys::Command_Not_Found, args[0].get_arg());
			}
		}

		else {
			if (flags.is_active(cmd::Only_CMD_Name)) {
				if (flags.is_active(cmd::Bee_Base)) sys::only_name_help(sys::Base);
				else if (flags.is_active(cmd::Instruction)) sys::only_name_help(sys::Instruction);
				else sys::only_name_help();
			}
			else if (flags.is_active(cmd::Bee_Base)) 
				util::foreach(util::filter<cmd::CMD_Data>(cmd::commands, 
					[](cmd::CMD_Data cmd) { return sys::is_cmd_same_type(cmd, sys::Base); }
				), sys::help);
			else if (flags.is_active(cmd::Instruction))
				util::foreach(util::filter<cmd::CMD_Data>(cmd::commands,
					[](cmd::CMD_Data cmd) { return sys::is_cmd_same_type(cmd, sys::Instruction); }
				), sys::help);

			else util::foreach(cmd::commands, sys::help);
		}
		break;
				
	case cmd::Clear:
		std::system("cls");
		break;

	case cmd::Color:
		for (std::string color : os::STRColors)
			std::cout << os::clr(color, util::string_to_color(color)) << std::endl;
		break;

	case cmd::Color_Mode:
		for (std::string cmode : os::STRColors_mode)
			std::cout << os::clr(cmode, os::WHITE, util::string_to_color_mode(cmode)) << std::endl;
		break;

	case cmd::Errs:
		for (sys::Error err : sys::errs)
			std::cout << os::clr(err.name, os::WT_RED) << std::endl;
		break;

	case cmd::Warns:
		for (sys::Warning warn : sys::warns)
			std::cout << os::clr(warn.name, os::WT_YELLOW) << std::endl;
		break;

	case cmd::CD:
		if (util::_args(system, args, cmd::CD)) break;

		if (!hand::exist_folder(path + args[0])) system.error(sys::Invalid_Path_Dir, args[0].get_arg());
		else path.cd(args[0].get_arg());
		break;

	case cmd::Diagnostic: {
		std::vector<cmd::Diag_data> ents;

		bool dir_size, path_dbg;

		dir_size = (flags.is_active(cmd::Dirs_size)) ? true : false;
		path_dbg = (flags.is_active(cmd::Path_debug)) ? true : false;

		if (path_dbg) std::cout << os::scroll_up(3) << os::up_ln() << os::up_ln() << os::up_ln();

		for (std::string ent : util::get_folder_ent(path.get_path()))
		{
			util::EntType type = util::get_ent_type(path + ent);
			std::string s_type = ((type == util::File) ? "File" : "Dirs");
			float byte_size = (dir_size && type == util::Folder) ? (float)util::sizeof_folder(path + ent, path_dbg) :
				(float)util::sizeof_file(path + ent);

			float f_size = ((byte_size < 1000)
				? byte_size : (byte_size >= 1000 && byte_size < 1000000)
				? byte_size / 1000 : (byte_size >= 1000000 && byte_size < 1000000000)
				? byte_size / 1000000 : (byte_size >= 1000000000)
				? byte_size / 1000000000 : -1);

			std::string f_sufix = ((byte_size < 1000) ? "BT" :
				(byte_size >= 1000 && byte_size < 1000000) ? "KB" :
				(byte_size >= 1000000 && byte_size < 1000000000) ? "MB" :
				(byte_size >= 1000000000) ? "GB" : "BIG");

			ents.push_back(cmd::Diag_data(ent, type, s_type, byte_size, f_size, f_sufix, util::is_hidden(path + ent)));
		}

		for (cmd::Diag_data ent : ents)
		{
			std::cout << os::clr(ent.s_type, ((ent.ent_type == util::File) ? os::WT_CYAN : os::CYAN));

			if (ent.ent_type == util::File || dir_size)
			{
				std::cout << os::get_clr(os::WT_YELLOW) << std::setw(8) << std::fixed;
				std::cout.precision((ent.byte_size >= 1000) ? 2 : 0);

				std::cout << std::right << ent.size;
				std::cout << " " << ent.size_sufix;

				std::cout << os::get_clr();
			}
			else std::cout << std::setw(13);

			std::cout << "  " << ((ent.is_hidden) ? os::clr(ent.name, os::WT_GREEN) : ent.name) << std::endl;
		}
		break;
	}

	case cmd::Print:
		if (args.get().size() && args[0].get_arg() != "") {
			for (cmd::Arg arg : args.get()) std::cout << arg.get_arg();
			if (!flags.is_active(cmd::Not_New_Line)) std::cout << std::endl;
		}
		std::cout << os::get_clr();
		break;

	case cmd::Add: {
		if (dbase.exist_shortcut(args[0].get_arg())) {
			system.error(sys::Unavaliable_Name, args[0].get_arg());
			break;
		}

		std::vector<std::string> block;
		std::string buffer;

		if (util::_args(system, args, cmd::Add)) break;
	    for (std::string line : util::split_string(util::join_string(util::get_from(args.get_str(false), 1)), ';')) {
			while (line[0] == ' ') line = util::erase_first(line);
			while (line[line.size() - 1] == ' ') line = util::erase_last(line);

			block.push_back(line);
		}

		if (dbase.exist_function(args[0].get_arg())) dbase.get_function(args[0].get_arg())->set_block(block);
		else dbase.add_function(dt::Function(args[0].get_arg(), block));
		break;
	}

	case cmd::Rmv:
		if (util::_args(system, args, cmd::Rmv)) break;
		if (dbase.exist_function(args[0].get_arg())) dbase.del_function(args[0].get_arg());
		else system.error(sys::Function_Not_Found_Err, args[0].get_arg());
		break;

	case cmd::Return:
		if (util::_args(system, args, cmd::Return)) break;
		if (parent_func) parent_func->set_return_value(args[0].get_arg());
		break;

	case cmd::Set:
		if (util::_args(system, args, cmd::Set)) break;
		if (dbase.exist_function(args[0].get_arg())) system.error(sys::Unavaliable_Name, args[0].get_arg());
		if (dbase.exist_shortcut(args[0].get_arg()) && !dbase.is_predef_shortcut(args[0].get_arg())) dbase.get_shortcut(args[0].get_arg())->set_value(args[1].get_arg());
		else if (!dbase.is_predef_shortcut(args[0].get_arg())) dbase.add_shortcut(dt::Shortcut(args[0].get_arg(), args[1].get_arg()));
		break;

	case cmd::Del:
		if (util::_args(system, args, cmd::Del)) break;
		if (dbase.exist_shortcut(args[0].get_arg()) && !dbase.is_predef_shortcut(args[0].get_arg())) dbase.del_shortcut(args[0].get_arg());
		else system.error(sys::Shortcut_Not_Found_Err, args[0].get_arg());
		break;

	case cmd::List:
		if (args.get().size() == 0) {
			for (dt::Shortcut st : dbase.get_all_shortcut()) {
				std::cout << std::setw(30);
				std::cout << std::left << os::clr(st.get_name(), ((dbase.is_predef_shortcut(st.get_name())) ? os::WT_BLUE : os::WT_CYAN)) << std::right << os::clr('\"' + st.get_value() + '\"', os::GREEN) << std::endl;
			}

			for (dt::Function fc : dbase.get_all_function()) {
				if (dbase.is_predef_function(fc.get_name())) continue;
				std::cout << std::setw(30);
				std::cout << std::left << os::clr(fc.get_name(), os::WT_CYAN) << std::right << '{' + os::clr("...", os::WT_GREEN) + '}' << std::endl;
			}
		}

		else if (args.get().size() == 1) {
			if (dbase.exist_shortcut(args[0].get_arg())) std::cout << dbase.get_shortcut(args[0].get_arg())->get_value() << std::endl;
			else if (dbase.exist_function(args[0].get_arg()))
				for (std::string line : dbase.get_function(args[0].get_arg())->get_block())
					std::cout << line << std::endl;
		}

		break;

	case cmd::Mfile:
		if (util::_args(system, args, cmd::Mfile)) break;
		if (hand::exist_file(util::_fmt(path, args[0]))) {
			if (system.ask(sys::Replace_File)) util::create_file(util::_fmt(path, args[0]));
		}
		else util::create_file(util::_fmt(path, args[0]));
		break;

	case cmd::RMfile:
		if (util::_args(system, args, cmd::RMfile)) break;
		if (hand::exist_file(util::_fmt(path, args[0]))) util::remove_file(util::_fmt(path, args[0]));
		else system.error(sys::Invalid_Path_File, args[0].get_arg());
		break;

	case cmd::Mdir:
		if (util::_args(system, args, cmd::Mdir)) break;
		util::create_folder(util::_fmt(path, args[0]));
		break;

	case cmd::RMdir:
		std::cout << os::scroll_up(3) << os::up_ln() << os::up_ln() << os::up_ln();
		if (util::_args(system, args, cmd::RMfile)) break;
		if (!hand::exist_folder(util::_fmt(path, args[0]))) {
			system.error(sys::Invalid_Path_Dir, args[0].get_arg());
			break;
		}

		if (util::get_folder_ent(util::_fmt(path, args[0])).size() == 0) util::remove_folder(util::_fmt(path, args[0]));
		else if (system.ask(sys::Remove_Not_Empty_Dir)) util::remove_not_empty_folder(util::_fmt(path, args[0]), flags.is_active(cmd::Path_debug));
		break;

	case cmd::Rename:
		if (util::_args(system, args, cmd::Rename)) break;
		util::rename_f(util::_fmt(path, args[0]), args[1].get_arg());
		break;

	case cmd::Sizeof:
		if (util::_args(system, args, cmd::Sizeof)) break;
		if (!hand::exist_file(util::_fmt(path, args[0]))) system.error(sys::Invalid_Path_File, args[0].get_arg());
		else if (!parent_func) std::cout << util::sizeof_file(util::_fmt(path, args[0])) << std::endl;
		else parent_func->set_return_value(std::to_string(util::sizeof_file(util::_fmt(path, args[0]))));
		break;

	case cmd::Lineof:
		if (util::_args(system, args, cmd::Lineof)) break;
		if (!hand::exist_file(util::_fmt(path, args[0]))) system.error(sys::Invalid_Path_File, args[0].get_arg());
		else if (!parent_func) std::cout << util::lineof_file(util::_fmt(path, args[0])) << std::endl;
		else parent_func->set_return_value(std::to_string(util::lineof_file(util::_fmt(path, args[0]))));
		break;

	case cmd::Read: {
		if (util::_args(system, args, cmd::Read)) break;
		if (!hand::exist_file(util::_fmt(path, args[0]))) system.error(sys::Invalid_Path_File, args[0].get_arg());
		else if (!parent_func) {
			for (std::string line : util::read_file(util::_fmt(path, args[0])))
				std::cout << line << std::endl;
		}
		else parent_func->set_return_value(util::join_string(util::read_file(util::_fmt(path, args[0])), "\n"));
		break;
	}
				
	case cmd::Write:
		if (util::_args(system, args, cmd::Write)) break;
		if (!hand::exist_file(util::_fmt(path, args[0]))) system.error(sys::Invalid_Path_File, args[0].get_arg());
		else util::write_file(util::_fmt(path, args[0]), args[1].get_arg(), ((flags.is_active(cmd::Clear_File)) ? std::ios::out : std::ios::app), (!flags.is_active(cmd::Not_New_Line)));
		break;

	case cmd::Run:
		if (util::_args(system, args, cmd::Run)) break;
		std::system(args[0].get_arg().c_str());
		break;

	case cmd::Stat: {
		MEMORYSTATUSEX stat = util::get_mem_stat();
		char ch;

		if (flags.is_active(cmd::Update))
			while ((ch = ((_kbhit()) ? is::get_ch() : 0)) == 0) {
				stat = util::get_mem_stat();
				sys::OS_stat(stat, true);
			}
		else sys::OS_stat(stat);
		break;
	}

	case cmd::Kpress:
		if (parent_func && is::k_hit())	parent_func->set_return_value(util::str_char(is::get_ch()));
		else if (is::k_hit()) std::cout << is::get_ch() << std::endl;
		break;

	case cmd::If:
		if (util::_args(system, args, cmd::If)) break;
		if (args[0].get_arg() == "true") {
			util::exec_block(system, sys_config, defs, path, util::get_from(args.get_str(), 1), dbase, parent_func);
			can_use_else_statement = false;
		}
		else can_use_else_statement = true;
		break;

	case cmd::Else:
		if (util::_args(system, args, cmd::Else)) break;
		if (!can_use_else_statement) break;
		else util::exec_block(system, sys_config, defs, path, util::get_from(args.get_str(), 0), dbase, parent_func);
		can_use_else_statement = false;

	case cmd::While:
		if (util::_args(system, args, cmd::While)) break;
		while (args[0].get_arg() == "true") {
			util::exec_block(system, sys_config, defs, path, util::get_from(args.get_str(), 1), dbase, parent_func);
			args = util::format_args_all(system, sys_config, defs, path, parent_func, s_buff, dbase);
		}
		break;

	case cmd::Not_found:
		system.error(sys::Command_Not_Found, s_buff[0]);
		break;
	}

	
}