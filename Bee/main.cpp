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

#include "src/Source/Cmds/Diagnostic/diag_data.h"
#include "src/Source/Cmds/commands.h"
#include "src/Source/Cmds/cmd_args.h"
#include "src/Source/Cmds/cmd_data.h"
#include "src/Source/Cmds/cmd_flag.h"

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

	is::Buffer buff;

	vector<string> s_buff;
	cmd::CMD_Arg args;
	cmd::CMD_Flags flags;

	while (!_sys.abort)
	{
		cout << os::path(path);
		buff = is::get_line();

		while (util::starts_with(buff.get(), " ")) buff = util::erase_first(buff.get());
		while (util::ends_with(buff.get(), ' ')) buff = util::erase_last(buff.get());

		s_buff = ((buff.get_split().size() == 0) ? vector<string>({ "" }) : buff.get_split());

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
			args = util::format_args_all(s_buff);

			if (args.get().size() < cmd::arg_size(cmd::CD))
			{
				sys::warn(sys::Insufficient_Args);
				break;
			}

			if (!hand::exist_folder(path + args[0])) sys::error(sys::Invalid_Path, args[0].get_arg());
			else path.cd(args[0].get_arg());
			break;

		case cmd::Diagnostic: {
			cout << os::scroll_up(3) << os::up_ln() << os::up_ln() << os::up_ln();
			vector<cmd::Diag_data> ents;

			bool dir_size, path_dbg;
			args = util::format_args_all(s_buff);
			flags = cmd::check_flags(args);

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
			args = util::format_args_all(s_buff);
			for (cmd::Arg arg : args.get())
				cout << arg.get_arg();
			cout << endl;
			break;

		case cmd::Not_found:
			sys::error(sys::Error(sys::Command_Not_Found), s_buff[0]);
			break;
		}
	}
}