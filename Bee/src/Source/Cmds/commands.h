#pragma once

#include <string>
#include <vector>

#include "../Stream/istream.h"

#include "cmd_data.h"

namespace cmd
{
	const std::vector<cmd::CMD_Data> commands =
	{
		cmd::CMD_Data(Exit),
		cmd::CMD_Data(Setting),
		cmd::CMD_Data(Detail),
		cmd::CMD_Data(Help),
		cmd::CMD_Data(Clear),

		cmd::CMD_Data(Color),
		cmd::CMD_Data(Errs),
		cmd::CMD_Data(Warns),

		cmd::CMD_Data(CD),
		cmd::CMD_Data(Diagnostic),
		cmd::CMD_Data(Print),

		cmd::CMD_Data(Add),
		cmd::CMD_Data(Rmv),
		cmd::CMD_Data(Return),

		cmd::CMD_Data(Set),
		cmd::CMD_Data(Del),
		cmd::CMD_Data(List),
		
		cmd::CMD_Data(Mfile),
		cmd::CMD_Data(RMfile),
		cmd::CMD_Data(Mdir),
		cmd::CMD_Data(RMdir),
		cmd::CMD_Data(Rename),
		cmd::CMD_Data(Sizeof),
		cmd::CMD_Data(Lineof),
		cmd::CMD_Data(Read),
		cmd::CMD_Data(Write),

		cmd::CMD_Data(Run),
		cmd::CMD_Data(Stat)
	};

	Command check(is::Buffer buff)
	{
		if (buff == "") return Null;

		else if (buff == ".x" || buff == ".exit" || buff == "exit" || buff == "quit" || buff == ".quit") return Exit;
		else if (buff == "setting" || buff == "config" || buff == ".sett" || buff == ".conf" || buff == "*") return Setting;
		else if (buff == ".d" || buff == ".detail" || buff == "detail") return Detail;
		else if (buff == ".h" || buff == ".help" || buff == "help") return Help;
		else if (buff == "clear" || buff == "clean" || buff == ".cl") return Clear;


		else if (buff == "color" || buff == "clr") return Color;
		else if (buff == "errs" || buff == "erros" || buff == "err") return Errs;
		else if (buff == "warns" || buff == "warn") return Warns;


		else if (buff == "cd") return CD;
		else if (buff == "diag" || buff == "diagnostic") return Diagnostic;
		else if (buff == "print") return Print;


		else if (buff == "add") return Add;
		else if (buff == "rmv" || buff == "remove") return Rmv;
		else if (buff == "return") return Return;


		else if (buff == "set") return Set;
		else if (buff == "del") return Del;
		else if (buff == "list") return List;


		else if (buff == "mfile" || buff == "make_file") return Mfile;
		else if (buff == "rmfile" || buff == "remove_file") return RMfile;
		else if (buff == "mdir" || buff == "make_dir") return Mdir;
		else if (buff == "rmdir" || buff == "remove_dir") return RMdir;
		else if (buff == "rename") return Rename;
		else if (buff == "sizeof") return Sizeof;
		else if (buff == "lineof") return Lineof;
		else if (buff == "read") return Read;
		else if (buff == "write") return Write;


		else if (buff == "run") return Run;
		else if (buff == "stat" || buff == "stats" || buff == "status" || buff == ".s") return Stat;

		else return Not_found;
	}
}