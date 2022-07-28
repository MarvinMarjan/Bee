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
		cmd::CMD_Data(Detail),
		cmd::CMD_Data(Help),
		cmd::CMD_Data(Clear),
		cmd::CMD_Data(CD),
		cmd::CMD_Data(Diagnostic)
	};

	Command check(is::Buffer buff)
	{
		if (buff == "")
			return Null;

		else if (buff == ".x" || buff == ".exit" || buff == "exit" || buff == "quit" || buff == ".quit")
			return Exit;

		else if (buff == ".d" || buff == ".detail" || buff == "detail")
			return Detail;

		else if (buff == ".h" || buff == ".help" || buff == "help")
			return Help;

		else if (buff == "clear" || buff == "clean")
			return Clear;



		else if (buff == "cd")
			return CD;

		else if (buff == "diag" || buff == "diagnostic")
			return Diagnostic;

		else
			return Not_found;
	}
}