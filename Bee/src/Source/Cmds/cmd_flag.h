#pragma once

#include "cmd_args.h"

#include <string>
#include <vector>

namespace cmd
{
	enum Flags
	{
		Dirs_size,
		Path_debug,

		Not_New_Line,
		Clear_File,

		Update
	};

	class CMD_Flags
	{
	public:
		CMD_Flags() {};
		CMD_Flags(std::vector<Flags> flags) { this->flags = flags; }

		inline bool is_active(Flags flag)
		{
			for (Flags f : this->flags)
				if (f == flag)
					return true;

			return false;
		}

	private:
		std::vector<Flags> flags;
	};

	std::vector<Flags> check_flags(cmd::CMD_Arg args)
	{
		std::vector<Flags> flags;

		for (Arg arg : args.get())
		{
			std::string flag = arg.get_flag();

			if (arg.get_flag() == "") continue;

			else if (flag == "ds") flags.push_back(Dirs_size);
			else if (flag == "pd") flags.push_back(Path_debug);

			else if (flag == "nl") flags.push_back(Not_New_Line);
			else if (flag == "cf") flags.push_back(Clear_File);

			else if (flag == "up") flags.push_back(Update);
		}

		return flags;
	}
}