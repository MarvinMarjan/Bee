#pragma once

#include <string>
#include <vector>

#include "../../System/System/system_warn.h"
#include "../../System/System/system.h"

#include "../Data/Shortcut/shortcut.h"

#include "../Cmds/cmd_data.h"

namespace util
{
	std::vector<std::string> format_args1(std::vector<std::string> src, dt::DBase dbase)
	{
		std::vector<std::string> f_src;

		src.erase(src.begin());

		for (size_t i = 0; i < src.size(); i++)
		{
			if (src[i][0] == '\"' && src[i].size() > 1)
			{
				std::string aux = "";

				for (i; i < src.size(); i++)
				{
					aux += src[i] + ((src[i][src[i].size() - 1] == '\"') ? "" : " ");

					if (src[i][src[i].size() - 1] == '\"') break;
				}

				aux.erase(0, 1);
				aux.erase(aux.size() - 1);

				f_src.push_back(aux);
			}

			else if (src[i][0] == '$')
			{
				std::string name = src[i];
				name.erase(0, 1);

				if (dbase.exist_shortcut(name)) f_src.push_back(dbase.get_shortcut(name)->get_value());
				else
				{
					sys::warn(sys::Shortcut_Not_Found_Warn, src[i]);
					f_src.push_back(src[i]);
				}
			}

			else f_src.push_back(src[i]);
		}

		return f_src;
	}

	std::vector<std::string> format_args2(std::vector<std::string> src)
	{
		std::vector<std::string> f_src = src;

		for (size_t i = 0; i < f_src.size(); i++)
		{
			if (f_src[i] == "+")
			{
				if (i + 1 >= f_src.size() || i == 0) sys::warn(sys::Incomplete_Expression);
				else
				{
					f_src[i - 1] = f_src[i - 1] + f_src[i + 1];

					f_src.erase(f_src.begin() + (i), f_src.begin() + (i + 2));
					i--;
				}
			}
		}

		return f_src;
	}

	inline std::vector<std::string> format_args_all(std::vector<std::string> src, dt::DBase dbase)
	{
		std::vector<std::string> f_src = format_args1(src, dbase);
		f_src = format_args2(f_src);

		return f_src;
	}

	inline bool _args(cmd::CMD_Arg args, cmd::Command cmd)
	{
		if (args.get().size() < cmd::arg_size(cmd))
		{
			sys::warn(sys::Insufficient_Args);
			return true;
		}

		return false;
	}
}