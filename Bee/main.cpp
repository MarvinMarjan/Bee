#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>
#include <vector>

#include "src/System/Handle/path_handling.h"
#include "src/System/Bootstrap/bootstrap.h"

#include "src/System/System/system_err.h"
#include "src/System/System/system.h"

#include "src/Source/Stream/ostream_snippet.h"
#include "src/Source/Stream/ostream_clr.h"
#include "src/Source/Stream/istream.h"

#include "src/Source/Data/Shortcut/shortcut.h"
#include "src/Source/Data/data.h"

#include "src/Source/Cmds/Diagnostic/diag_data.h"
#include "src/Source/Cmds/commands.h"
#include "src/Source/Cmds/cmd_args.h"
#include "src/Source/Cmds/cmd_data.h"
#include "src/Source/Cmds/cmd_flag.h"

#include "src/Source/Operator/OP_Repeat/op_iterator.h"
#include "src/Source/Operator/op_process.h"
#include "src/Source/Operator/operator.h"

#include "src/Source/Util/string_util.h"
#include "src/Source/Util/cmd_util.h"
#include "src/Source/Util/filesys_util.h"

using namespace std;

inline std::ostream& operator<<(std::ostream& os, hand::Path path)
{
	return (os << path.get_path());
}

inline std::ostream& operator<<(std::ostream& os, is::Buffer buff)
{
	return (os << buff.get());
}

int main(int argc, char* argv[])
{
	system("color");

	sys::System _sys;
	bt::Bootstrap boot;
	
	hand::Path path(boot);
	path = util::swap(path.get_path(), '\\', '/');

	dt::DBase dbase("src/Source/Data/DBase/shortcuts.txt");
	if (dbase.fail) sys::warn(sys::DataBase_Bootstrap_Err);

	is::Buffer buff;
	vector<string> s_buff;

	cmd::CMD_Arg args;
	cmd::CMD_Flags flags;

	op::OP_Aux op_aux;

	cin.get();

	while (!_sys.abort)
	{
		if (op_aux.repeat.is && op_aux.repeat.itr >= op_aux.repeat.times)
		{
			_sys.blocked = false;
			op_aux.repeat.itr = 0;
			op_aux.repeat.is = false;
		}

		if (!_sys.blocked)
		{
			cout << os::path(path);
			buff = is::get_line();

			while (util::starts_with(buff.get(), " ")) buff = util::erase_first(buff.get());
			while (util::ends_with(buff.get(), ' ')) buff = util::erase_last(buff.get());

			s_buff = ((buff.get_split().size() == 0) ? vector<string>({ "" }) : buff.get_split());
			args = util::format_args_all(s_buff, dbase);

			flags = cmd::check_flags(args);
			args.erase_flags();
		}

		if (cmd::check(s_buff[0]) == cmd::Not_found && !op_aux.repeat.is)
			switch (op::check(s_buff[0][0]))
			{
			case op::OP_Repeat:
				op_aux.repeat.times = stoi(util::erase_first(s_buff[0]));
				op_aux.repeat.is = true;
				_sys.blocked = true;

				buff = util::join_string(args.get_str());
				s_buff.erase(s_buff.begin());
				args = util::format_args_all(s_buff, dbase);
				args.erase_flags();

				continue;
			}

		switch (cmd::check(s_buff[0]))
		{
		case cmd::Null: continue;
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
			cout << os::scroll_up(3) << os::up_ln() << os::up_ln() << os::up_ln();
			vector<cmd::Diag_data> ents;

			bool dir_size, path_dbg;

			dir_size = (flags.is_active(cmd::Dirs_size)) ? true : false;
			path_dbg = (flags.is_active(cmd::Path_debug)) ? true : false;

			for (string ent : util::get_folder_ent(path.get_path()))
			{
				util::EntType type = util::get_ent_type(path + ent);
				string s_type = ((type == util::File) ? "File" : "Dirs");
				float byte_size = (dir_size && type == util::Folder) ? (float)util::sizeof_folder(path + ent, path_dbg) :
																		(float)util::sizeof_file(path + ent);

				float f_size = ((byte_size < 1000)
					? byte_size : (byte_size >= 1000 && byte_size < 1000000)
					? byte_size / 1000 : (byte_size >= 1000000 && byte_size < 1000000000)
					? byte_size / 1000000 : (byte_size >= 1000000000)
					? byte_size / 1000000000 : -1);

				string f_sufix = ((byte_size < 1000) ? "BT" :
					(byte_size >= 1000 && byte_size < 1000000) ? "KB" :
					(byte_size >= 1000000 && byte_size < 1000000000) ? "MB" :
					(byte_size >= 1000000000) ? "GB" : "BIG");

				ents.push_back(cmd::Diag_data(ent, type, s_type, byte_size, f_size, f_sufix, util::is_hidden(path + ent)));
			}

			for (cmd::Diag_data ent : ents)
			{
				cout << os::clr(ent.s_type, ((ent.ent_type == util::File) ? os::WT_CYAN : os::CYAN));

				if (ent.ent_type == util::File || dir_size)
				{
					cout << os::get_clr(os::WT_YELLOW) << setw(8) << fixed;
					cout.precision((ent.byte_size >= 1000) ? 2 : 0);

					cout << right << ent.size;
					cout << " " << ent.size_sufix;

					cout << os::get_clr();
				}
				else cout << setw(13);

				cout << "  " << ((ent.is_hidden) ? os::clr(ent.name, os::WT_GREEN) : ent.name) << endl;
			}
			break;
		}

		case cmd::Print:
			for (cmd::Arg arg : args.get()) cout << arg.get_arg();
			if (!flags.is_active(cmd::Not_New_Line)) cout << endl;
			break;

		case cmd::Add:
			if (util::_args(args, cmd::Add)) break;
			break;
			// under development

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
				cout << os::clr(st.get_name(), os::WT_CYAN) << "  " << os::clr('\"' + st.get_value() + '\"', os::GREEN) << endl;
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
			else cout << util::sizeof_file(args[0].get_arg()) << endl;
			break;

		case cmd::Lineof:
			if (util::_args(args, cmd::Lineof)) break;
			cout << util::lineof_file(args[0].get_arg()) << endl;
			break;

		case cmd::Read:
			if (util::_args(args, cmd::Read)) break;
			if (!hand::exist_file(args[0].get_arg())) sys::error(sys::Invalid_Path_File, args[0].get_arg());
			else for (string line : util::read_file(args[0].get_arg()))
					cout << line << endl;
			break;

		case cmd::Write:
			if (util::_args(args, cmd::Write)) break;
			if (!hand::exist_file(args[0].get_arg())) sys::error(sys::Invalid_Path_File, args[0].get_arg());
			else util::write_file(args[0].get_arg(), args[1].get_arg(), ((flags.is_active(cmd::Clear_File)) ? ios::out : ios::app), (!flags.is_active(cmd::Not_New_Line)));
			break;


		case cmd::Not_found:
			sys::error(sys::Error(sys::Command_Not_Found), s_buff[0]);
			break;
		}

		if (op_aux.repeat.is) op_aux.repeat.itr += 1;
	}
}