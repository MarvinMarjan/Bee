#include "src/System/Exec/exec.h"

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
	bt::Bootstrap_Flag btflag = bt::check_bt_flag(argc, argv);
	bt::BootMode mode = bt::get_bt_mode(argc, argv, _sys.mode_arg_index);
	
	if (btflag.is_active(bt::HideWindow)) util::set_window(util::Hidden);

	hand::Path path(boot);
	path = util::swap(path.get_path(), '\\', '/');

	dt::DBase dbase("src/Source/Data/DBase/shortcuts.txt");
	if (dbase.fail) sys::warn(sys::DataBase_Bootstrap_Err);

	is::Buffer buff;
	vector<string> s_buff;

	cmd::CMD_Arg args;
	cmd::CMD_Flags flags;

	while (!_sys.abort)
	{
		if (!btflag.is_active(bt::HidePath) || mode == bt::Default) cout << os::path(path);
		if (mode == bt::Default) buff = is::get_line();

		else if (mode == bt::InlineCMD)
		{
			buff = (string)argv[_sys.mode_arg_index + _sys.inline_mode_arg_itr];
			buff = util::swap(buff.get(), '\'', '\"');
		}

		while (util::starts_with(buff.get(), " ")) buff = util::erase_first(buff.get());
		while (util::ends_with(buff.get(), ' ')) buff = util::erase_last(buff.get());

		s_buff = ((buff.get_split().size() == 0) ? vector<string>({ "" }) : buff.get_split());
		args = util::format_args_all(s_buff, dbase);

		flags = cmd::check_flags(args);

		if (cmd::check(s_buff[0]) == cmd::Not_found && !dbase.exist_function(s_buff[0]))
		{
			switch (op::check(s_buff[0][0]))
			{
			case op::Null: break;
			case op::OP_Repeat: {
				s_buff[0] = util::erase_first(s_buff[0]);
				size_t times = stoi(s_buff[0]);
				buff = util::join_string(args.get_str());
				args.erase_first();
				s_buff = ((buff.get_split().size() == 0) ? vector<string>({ "" }) : buff.get_split());
				for (size_t i = 0; i < times; i++) run(_sys, path, dbase, buff, s_buff, args, flags);
			}
			}

			if (op::check(s_buff[0][0]) != op::Null) continue;
		}

		if (mode != bt::Default && !btflag.is_active(bt::HidePath)) cout << buff << endl;

		run(_sys, path, dbase, buff, s_buff, args, flags);

		if (mode == bt::InlineCMD)
		{
			if (_sys.inline_mode_arg_itr >= argc - _sys.mode_arg_index - 1) _sys.abort = true;
			else _sys.inline_mode_arg_itr++;
		}
	}

	if (mode != bt::Default && btflag.is_active(bt::Pause)) is::get_ch();
}