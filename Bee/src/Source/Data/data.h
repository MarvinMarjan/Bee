#pragma once

#include "../Util/filesys_util.h"
#include "../Util/string_util.h"

#include "../../System/System/system_setting.h"
#include "Shortcut/shortcut.h"
#include "Function/function.h"

#include <string>
#include <vector>

namespace dt
{
	class DBase
	{
	public:
		DBase() {};
		DBase(std::string path)
		{
			if (!hand::exist_file(path))
			{
				this->fail = true;
				return;
			}

			this->path = path;
			std::vector<std::string> lines = util::read_file(path);

			for (std::string line : lines)
			{
				if (line == "") continue;
				std::vector<std::string> s_line = util::split_string(line);
				this->add_shortcut(Shortcut(s_line[0], util::join_string(s_line, " ", 1)));
			}

			this->fail = false;
		}

		~DBase()
		{
			std::string content = "";

			for (Shortcut scut : this->shortcut)
				content += scut.get_name() + ((scut.get_value() != "") ? " " : "") + scut.get_value() + "\n";

			util::write_file(this->path, content, std::ios::out, false);
		}

		inline void del_shortcut(std::string name)
		{
			for (size_t i = 0; i < this->shortcut.size(); i++)
				if (this->shortcut[i].get_name() == name)
					this->shortcut.erase(this->shortcut.begin() + i);
		}

		inline void del_function(std::string name)
		{
			for (size_t i = 0; i < this->shortcut.size(); i++)
				if (this->function[i].get_name() == name)
					this->function.erase(this->function.begin() + i);
		}

		inline void add_shortcut(Shortcut shortcut) { this->shortcut.push_back(shortcut); }
		inline void add_function(Function function) { this->function.push_back(function); }

		inline Shortcut* get_shortcut(std::string name)
		{
			for (size_t i = 0; i < this->shortcut.size(); i++)
				if (this->shortcut[i].get_name() == name)
					return &this->shortcut[i];

			return nullptr;
		}

		inline Function* get_function(std::string name)
		{
			for (size_t i = 0; i < this->function.size(); i++)
				if (this->function[i].get_name() == name)
					return &this->function[i];

			return nullptr;
		}

		inline std::vector<Shortcut> get_all_shortcut() { return this->shortcut; }
		inline std::vector<Function> get_all_function() { return this->function; }

		inline bool exist_shortcut(std::string name)
		{
			for (size_t i = 0; i < this->shortcut.size(); i++)
				if (this->shortcut[i].get_name() == name)
					return true;

			return false;
		}

		inline bool exist_function(std::string name)
		{
			for (size_t i = 0; i < this->function.size(); i++)
				if (this->function[i].get_name() == name)
					return true;

			return false;
		}

		bool fail;

	private:
		std::vector<Shortcut> shortcut;
		std::vector<Function> function;

		// crie uma classe propria para todas as configurações do sistema (class System_Settings)


		/*std::vector<sys::Sys_Setting> setting =
		{
			sys::Sys_Setting("Caret_Color", "UNDERLINE_RED")
		};*/


		std::string path;

	};
}