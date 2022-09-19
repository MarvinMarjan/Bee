#pragma once

#include "../../Source/Stream/istream.h"
#include "../../System/System/system.h"

#include "../../Source/Util/cmd_util.h"

namespace util
{
	void exec_block(sys::System& system, sys::System_Settings& sys_config, sys::Defs& defs, hand::Path& path, std::vector<std::string> src_block,
		dt::DBase& dbase, dt::Function* parent_func = nullptr)
	{
		std::string block = util::join_string(src_block);
		std::vector<std::string> lines = util::split_string(block, ';');

		for (size_t i = 0; i < lines.size(); i++) {
			while (lines[i][0] == ' ') lines[i] = util::erase_first(lines[i]);
			while (lines[i][lines[i].size() - 1] == ' ') lines[i] = util::erase_last(lines[i]);
		}

		for (std::string line : lines) {
			is::Buffer _buff = line;
			std::vector<std::string> _s_buff = _buff.get_split();
			cmd::CMD_Arg _args = util::format_args_all(system, sys_config, defs, path, parent_func, _s_buff, dbase);
			cmd::CMD_Flags _flags = cmd::check_flags(_args);
			_args.erase_flags();

			run(system, sys_config, defs, path, dbase, _buff, _s_buff, _args, _flags, parent_func);
		}
	}
}