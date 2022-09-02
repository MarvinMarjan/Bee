#pragma once

#include <string>
#include <vector>

#include "../../System/Exec/exec.h"

void run(sys::System& system, sys::System_Settings& sys_config, sys::Defs& defs, hand::Path& path, dt::DBase& dbase, is::Buffer& buff,
	std::vector<std::string> s_buff, cmd::CMD_Arg& args, cmd::CMD_Flags& flags, dt::Function* parent_func);

namespace util
{
	inline std::vector<std::string> format_args_all(sys::System& system, sys::System_Settings& sys_config, sys::Defs& defs, hand::Path& path, dt::Function* parent_func, std::vector<std::string>& src, dt::DBase& dbase);

	std::vector<std::string> format_args1(sys::System& system, sys::System_Settings& sys_config, sys::Defs& defs, hand::Path& path, dt::Function* parent_func, std::vector<std::string>& _src, dt::DBase& dbase, bool* ignore_fmt2 = nullptr)
	{
		std::vector<std::string> f_src;
		std::vector<std::string> src = _src;

		src.erase(src.begin());

		for (size_t i = 0; i < src.size(); i++)
		{
			if (src[i][0] == '*') {
				f_src.push_back(util::erase_first(src[i]));
				_src[i + 1] = util::erase_first(_src[i + 1]);
			}

			else if (src[i][0] == '\"' && src[i].size() > 1)
			{
				std::string aux = "";

				for (i; i < src.size(); i++) {
					aux += src[i] + ((src[i][src[i].size() - 1] == '\"') ? "" : " ");

					if ((src[i][src[i].size() - 1] == '\"')) break;
				}

				aux.erase(0, 1);
				aux.erase(aux.size() - 1);

				f_src.push_back(aux);
			}

			else if (src[i][0] == '{' && src[i].size() > 1)
			{
				*ignore_fmt2 = true;

				std::vector<std::string> parts;
				std::string aux = "";

				for (i; i < src.size(); i++) {
					aux += src[i] + ((src[i][src[i].size() - 1] == '}') ? "" : " ");

					if ((src[i][src[i].size() - 1] == '}')) break;
				}

				aux.erase(0, 1);
				aux.erase(aux.size() - 1);

				std::vector<std::string> vec_aux = util::split_string(aux, ';');

				for (size_t o = 0; o < vec_aux.size(); o++)
				{
					while (util::starts_with(vec_aux[o], " ")) vec_aux[o] = util::erase_first(vec_aux[o]);
					while (util::ends_with(vec_aux[o], ' ')) vec_aux[o] = util::erase_last(vec_aux[o]);

					std::vector<std::string> vec_part = util::split_string(vec_aux[o]);
					
					for (std::string arg : vec_part) parts.push_back(arg);
					for (std::string part : parts) f_src.push_back(part);

					if (o + 1 < vec_aux.size()) f_src.push_back(";");
					parts.clear();
				}
			}

			else if (src[i][0] == '$') {
				std::string name = src[i];
				name.erase(0, 1);

				if (dbase.exist_shortcut(name)) f_src.push_back(dbase.get_shortcut(name)->get_value());
				else {
					system.warn(sys::Shortcut_Not_Found_Warn, src[i]);
					f_src.push_back(src[i]);
				}
			}

			else if (src[i][0] == '#')
			{
				if (src[i][1] == '(') {
					std::string joined = util::join_string(util::get_from(src, i));

					std::string func = util::sub_string(joined, 2, util::find_first(joined, ')'));
					std::vector<std::string> s_func = util::split_string(func);

					cmd::CMD_Arg f_args = format_args_all(system, sys_config, defs, path, parent_func, s_func, dbase);
					cmd::CMD_Flags flags = cmd::check_flags(f_args);

					f_args.erase_flags();

					is::Buffer buff = s_func[0] + ' ' + util::join_string(f_args.get_str());

					std::vector<std::string> s_buff = ((buff.get_split().size() == 0) ? std::vector<std::string>({ "" }) : buff.get_split());

					run(system, sys_config, defs, path, dbase, buff, s_buff, f_args, flags, parent_func);

					f_src.push_back(dbase.get_function(s_func[0])->get_return_value());

					while (src[i][src[i].size() - 1] != ')') i++;
				}

				else {
					std::string name = src[i];
					name.erase(0, 1);

					if (name == "input") {
						std::string buff;
						set_mouse_visible(True);
						std::getline(std::cin, buff);
						set_mouse_visible(False);
						f_src.push_back(buff);
					}
				}
			}

			else if (src[i][0] == '\\') {
				std::string name = src[i];
				name.erase(0, 1);
				
				if (util::string_to_color(name) != os::Nothing) f_src.push_back(os::get_clr(util::string_to_color(name)));
			}

			else f_src.push_back(src[i]);
		}

		return f_src;
	}

	std::vector<std::string> format_args2(sys::System& system, std::vector<std::string>& src)
	{
		std::vector<std::string> f_src = src;

		for (size_t i = 0; i < f_src.size(); i++)
		{
			if (f_src[i][0] == '*')
			{
				f_src.push_back(util::erase_first(src[i]));
				src[i + 1] = util::erase_first(src[i + 1]);
			}

			else if (f_src[i] == "+")
			{
				if (i + 1 >= f_src.size() || i == 0) system.warn(sys::Incomplete_Expression);
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

	inline std::vector<std::string> format_args_all(sys::System& system, sys::System_Settings& sys_config, sys::Defs& defs, hand::Path& path, dt::Function* parent_func, std::vector<std::string>& src, dt::DBase& dbase)
	{
		bool ignore_fmt2 = false;

		std::vector<std::string> f_src = format_args1(system, sys_config, defs, path, parent_func, src, dbase, &ignore_fmt2);
		if (!ignore_fmt2) f_src = format_args2(system, f_src);

		return f_src;
	}

	inline bool _args(sys::System& system, cmd::CMD_Arg args, cmd::Command cmd)
	{
		if (args.get().size() < cmd::arg_size(cmd)) {
			system.warn(sys::Insufficient_Args);
			return true;
		}

		return false;
	}

	inline std::string _fmt(hand::Path path, cmd::Arg arg)
	{
		if (hand::is_abs(arg.get_arg())) return arg.get_arg();
		else return path + arg.get_arg();
	}
}