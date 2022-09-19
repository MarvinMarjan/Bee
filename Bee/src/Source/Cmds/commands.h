#pragma once

#include <string>
#include <vector>

#include "../Util/array_util.h"

#include "../Stream/istream.h"

#include "cmd_data.h"

namespace cmd
{
	const std::vector<cmd::CMD_Data> commands =
	{
		cmd::CMD_Data(Exit),
		cmd::CMD_Data(Setting),
		cmd::CMD_Data(Get_Setting),
		cmd::CMD_Data(Detail),
		cmd::CMD_Data(Help),
		cmd::CMD_Data(Clear),

		cmd::CMD_Data(Color),
		cmd::CMD_Data(Color_Mode),
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
		cmd::CMD_Data(Stat),

		cmd::CMD_Data(Kpress),

		cmd::CMD_Data(If),
		cmd::CMD_Data(Else),
		cmd::CMD_Data(While)
	};

	inline Command check(is::Buffer buff)
	{
		for (CMD_Data command : commands)
			if (util::exist(buff.get(), command.name_variants))
				return command.adress;

		return Not_found;
	}
}