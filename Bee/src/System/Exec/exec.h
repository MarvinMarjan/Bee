#pragma once

#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>
#include <vector>

#include "../../../src/System/Handle/path_handling.h"
#include "../../../src/System/Bootstrap/bootstrap.h"

#include "../../../src/System/System/system_err.h"
#include "../../../src/System/System/system.h"

#include "../../../src/Source/Stream/ostream_snippet.h"
#include "../../../src/Source/Stream/ostream_clr.h"
#include "../../../src/Source/Stream/istream.h"

#include "../../../src/Source/Data/Shortcut/shortcut.h"
#include "../../../src/Source/Data/data.h"

#include "../../../src/Source/Cmds/Diagnostic/diag_data.h"
#include "../../../src/Source/Cmds/commands.h"
#include "../../../src/Source/Cmds/cmd_args.h"
#include "../../../src/Source/Cmds/cmd_data.h"
#include "../../../src/Source/Cmds/cmd_flag.h"

#include "../../../src/Source/Operator/operator.h"

#include "../../../src/Source/Util/string_util.h"
#include "../../../src/Source/Util/cmd_util.h"
#include "../../../src/Source/Util/filesys_util.h"

void run(sys::System& _sys, hand::Path& path, dt::DBase& dbase, is::Buffer& buff, 
	     std::vector<std::string> s_buff, cmd::CMD_Arg& args, cmd::CMD_Flags& flags)
{
	if (dbase.exist_function(s_buff[0]))
	{
		for (std::string line : dbase.get_function(s_buff[0])->get_block())
		{
			buff = line;
			s_buff = ((buff.get_split().size() == 0) ? std::vector<std::string>({ "" }) : buff.get_split());
			args = util::format_args_all(s_buff, dbase);

			flags = cmd::check_flags(args);
			args.erase_flags();

			run(_sys, path, dbase, buff, s_buff, args, flags);
		}

		return;
	}

	switch (cmd::check(s_buff[0]))
	{
	case cmd::Null: break;
	case cmd::Exit:
		_sys.abort = true;
		break;

	case cmd::Detail:
		sys::details();
		break;

	case cmd::Help:
		for (cmd::CMD_Data cmd : cmd::commands) sys::help(cmd);
		break;

	case cmd::Clear:
		system("cls");
		break;

	case cmd::CD:
		if (util::_args(args, cmd::CD)) break;

		if (!hand::exist_folder(path + args[0])) sys::error(sys::Invalid_Path_Dir, args[0].get_arg());
		else path.cd(args[0].get_arg());
		break;

	case cmd::Diagnostic: {
		std::cout << os::scroll_up(3) << os::up_ln() << os::up_ln() << os::up_ln();
		std::vector<cmd::Diag_data> ents;

		bool dir_size, path_dbg;

		dir_size = (flags.is_active(cmd::Dirs_size)) ? true : false;
		path_dbg = (flags.is_active(cmd::Path_debug)) ? true : false;

		for (std::string ent : util::get_folder_ent(path.get_path()))
		{
			util::EntType type = util::get_ent_type(path + ent);
			std::string s_type = ((type == util::File) ? "File" : "Dirs");
			float byte_size = (dir_size && type == util::Folder) ? (float) util::sizeof_folder(path + ent, path_dbg) :
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
		for (cmd::Arg arg : args.get()) std::cout << arg.get_arg();
		if (!flags.is_active(cmd::Not_New_Line)) std::cout << std::endl;
		break;

	case cmd::Add: {
		std::vector<std::string> block;
		std::string buffer;

		if (util::_args(args, cmd::Add)) break;
		if (args[1].get_arg() == "...") do
		{
			std::getline(std::cin, buffer);
			if (buffer != ";") block.push_back(buffer);
		} while (buffer != ";");
		dbase.add_function(dt::Function(args[0].get_arg(), block));
		break;
	}

	case cmd::Edit: {
		std::vector<std::string> block;
		std::string buffer;

		if (util::_args(args, cmd::Edit)) break;

		if (!dbase.exist_function(args[0].get_arg())) { sys::error(sys::Function_Not_Found_Err, args[0].get_arg()); break; }
		if (args[1].get_arg() == "...") do
		{
			std::getline(std::cin, buffer);
			if (buffer != ";") block.push_back(buffer);
		} while (buffer != ";");
		dbase.get_function(args[0].get_arg())->set_block(block);
		break;
	}

	case cmd::Set:
		if (util::_args(args, cmd::Set)) break;
		if (dbase.exist_shortcut(args[0].get_arg())) dbase.get_shortcut(args[0].get_arg())->set_value(args[1].get_arg());
		else dbase.add_shortcut(dt::Shortcut(args[0].get_arg(), args[1].get_arg()));
		break;

	case cmd::Del:
		if (util::_args(args, cmd::Del)) break;
		if (dbase.exist_shortcut(args[0].get_arg())) dbase.del_shortcut(args[0].get_arg());
		else sys::error(sys::Shortcut_Not_Found_Err, args[0].get_arg());
		break;

	case cmd::List:
		for (dt::Shortcut st : dbase.get_all_shortcut())
			std::cout << os::clr(st.get_name(), os::WT_CYAN) << "  " << os::clr('\"' + st.get_value() + '\"', os::GREEN) << std::endl;
		break;

	case cmd::Mfile:
		if (util::_args(args, cmd::Mfile)) break;
		util::create_file(args[0].get_arg());
		break;

	case cmd::RMfile:
		if (util::_args(args, cmd::RMfile)) break;
		if (hand::exist_file(args[0].get_arg())) util::remove_file(args[0].get_arg());
		else sys::error(sys::Invalid_Path_File, args[0].get_arg());
		break;

	case cmd::Mdir:
		if (util::_args(args, cmd::Mdir)) break;
		util::create_folder(args[0].get_arg());
		break;

	case cmd::RMdir:
		if (util::_args(args, cmd::RMfile)) break;
		if (hand::exist_folder(args[0].get_arg())) util::remove_folder(args[0].get_arg());
		else sys::error(sys::Invalid_Path_Dir, args[0].get_arg());
		break;

	case cmd::Rename:
		if (util::_args(args, cmd::Rename)) break;
		util::rename_f(args[0].get_arg(), args[1].get_arg());
		break;

	case cmd::Sizeof:
		if (util::_args(args, cmd::Sizeof)) break;
		if (!hand::exist_file(args[0].get_arg())) sys::error(sys::Invalid_Path_File, args[0].get_arg());
		else std::cout << util::sizeof_file(args[0].get_arg()) << std::endl;
		break;

	case cmd::Lineof:
		if (util::_args(args, cmd::Lineof)) break;
		std::cout << util::lineof_file(args[0].get_arg()) << std::endl;
		break;

	case cmd::Read:
		if (util::_args(args, cmd::Read)) break;
		if (!hand::exist_file(args[0].get_arg())) sys::error(sys::Invalid_Path_File, args[0].get_arg());
		else for (std::string line : util::read_file(args[0].get_arg()))
			std::cout << line << std::endl;
		break;

	case cmd::Write:
		if (util::_args(args, cmd::Write)) break;
		if (!hand::exist_file(args[0].get_arg())) sys::error(sys::Invalid_Path_File, args[0].get_arg());
		else util::write_file(args[0].get_arg(), args[1].get_arg(), ((flags.is_active(cmd::Clear_File)) ? std::ios::out : std::ios::app), (!flags.is_active(cmd::Not_New_Line)));
		break;


	case cmd::Not_found:
		sys::error(sys::Error(sys::Command_Not_Found), s_buff[0]);
		break;
	}
}