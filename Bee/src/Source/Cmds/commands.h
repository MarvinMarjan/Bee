#pragma once

#include "../Stream/istream.h"

namespace cmd
{
	enum Command
	{
		Null,
		Not_found,

		Exit,
		Detail
	};

	Command check(is::Buffer buff)
	{
		if (buff == "")
			return Null;

		else if (buff == ".x" || buff == ".exit" || buff == "exit" || buff == "quit" || buff == ".quit")
			return Exit;

		else if (buff == ".d" || buff == ".detail" || buff == "detail")
			return Detail;

		else
			return Not_found;
	}
}