#pragma once

#include "cmd_args.h"

#include <string>
#include <vector>

namespace cmd
{
	enum Flags
	{
		Dirs_size,
		Path_debug
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

			if (arg.get_flag() == "") return {};

			else if (flag == "ds") flags.push_back(Dirs_size);
			else if (flag == "pd") flags.push_back(Path_debug);
		}

		return flags;
	}
}