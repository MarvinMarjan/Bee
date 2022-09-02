// include all files
#include "src/System/Exec/exec.h"

inline std::ostream& operator<<(std::ostream& os, hand::Path path)
{
	return (os << path.get_path());
}

inline std::ostream& operator<<(std::ostream& os, is::Buffer buff)
{
	return (os << buff.get());
}

// main function
int main(int argc, char* argv[])
{
	//std::cout << util::linesof_folder("src") - util::linesof_folder("src/Deps") << std::endl;

	sys::System_Settings sys_config;
	sys::System system;
	sys::Defs defs;

	if (sys_config.fail) {
		system.warn(sys::Settings_Bootstrap_Err);
		sys_config.set_default_settings(sys::default_settings);
	}
	
	sys::set_defs(defs, sys_config);

	it::Itelli_Buffer it_buff;


	bt::Bootstrap boot;
	bt::Bootstrap_Flag btflag = bt::check_bt_flag(argc, argv);
	bt::BootMode mode = bt::get_bt_mode(argc, argv, system.mode_arg_index);


	if (mode == bt::ReadFile) {
		if (hand::exist_file(argv[system.mode_arg_index])) boot.src_file = util::read_file(argv[system.mode_arg_index]);
		else {
			system.error(sys::Invalid_Path_File, argv[system.mode_arg_index]);
			system.abort = true;
		}
	}
	
	if (btflag.is_active(bt::HideWindow)) util::set_window(util::Hidden);

	hand::Path path(boot);

	if (sys_config["initial_path"]->get_value() != "") path = sys_config["initial_path"]->get_value();
	else path = util::swap(path.get_path(), '\\', '/');

	dt::DBase dbase;
	if (dbase.fail) system.warn(sys::DataBase_Bootstrap_Err);

	is::Buffer buff;
	std::vector<std::string> s_buff;

	cmd::CMD_Arg args;
	cmd::CMD_Flags flags;

	while (!system.abort)
	{
		system.update(sys_config);

		if (system.use_itellisense) util::set_mouse_visible(util::False);
		else util::set_mouse_visible(util::True);

		if (!btflag.is_active(bt::HidePath) || mode == bt::Default) std::cout << os::path(path);
		if (mode == bt::Default) buff = ((system.use_itellisense) ? it::itelli_stdin(path, dbase, it_buff, defs.caret_color) : is::get_line());

		if (buff != "") it_buff.add_buff(buff);

		switch (mode)
		{
		case bt::InlineCMD:
			buff = (std::string)argv[system.mode_arg_index + system.inline_mode_arg_itr];
			buff = util::swap(buff.get(), '\'', '\"');
			break;

		case bt::ReadFile:
			buff = boot.src_file[system.readfile_mode_arg_itr];
		}

		while (util::starts_with(buff.get(), " ") || util::starts_with(buff.get(), "\t")) buff = util::erase_first(buff.get());
		while (util::ends_with(buff.get(), ' ') || util::ends_with(buff.get(), '\t')) buff = util::erase_last(buff.get());

		s_buff = ((buff.get_split().size() == 0) ? std::vector<std::string>({ "" }) : buff.get_split());
		args = util::format_args_all(system, sys_config, defs, path, nullptr, s_buff, dbase);

		flags = cmd::check_flags(args);
		args.erase_flags();

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
				s_buff = ((buff.get_split().size() == 0) ? std::vector<std::string>({ "" }) : buff.get_split());
				for (size_t i = 0; i < times; i++) run(system, sys_config, defs, path, dbase, buff, s_buff, args, flags);
				continue;
			}
			}

			if (op::check(s_buff[0][0]) != op::Null) continue;
		}

		if (mode != bt::Default && !btflag.is_active(bt::HidePath)) std::cout << buff << std::endl;

		run(system, sys_config, defs, path, dbase, buff, s_buff, args, flags);

		if (mode == bt::InlineCMD) {
			if (system.inline_mode_arg_itr >= argc - system.mode_arg_index - 1) system.abort = true;
			else system.inline_mode_arg_itr++;
		}

		if (mode == bt::ReadFile) {
			if (system.readfile_mode_arg_itr >= util::lineof_file(argv[system.mode_arg_index]) - 1) system.abort = true;
			else system.readfile_mode_arg_itr++;
		}
	}

	if ((mode != bt::Default || system.pause_sys) && (btflag.is_active(bt::Pause) || system.pause_sys)) is::get_ch();

	return EXIT_SUCCESS;
}