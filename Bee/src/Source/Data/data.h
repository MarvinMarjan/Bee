#pragma once

#include "../Util/filesys_util.h"
#include "../Util/string_util.h"
#include "Shortcut/shortcut.h"

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
				content += scut.get_name() + ((scut.get_value() != "") ? " " : "") + "\n";

			util::write_file(this->path, content);
		}

		inline void del_shortcut(std::string name)
		{
			for (size_t i = 0; i < this->shortcut.size(); i++)
				if (this->shortcut[i].get_name() == name)
					this->shortcut.erase(this->shortcut.begin() + i);
		}

		inline void add_shortcut(Shortcut shortcut) { this->shortcut.push_back(shortcut); }
		inline Shortcut* get_shortcut(std::string name)
		{
			for (size_t i = 0; i < this->shortcut.size(); i++)
				if (this->shortcut[i].get_name() == name)
					return &this->shortcut[i];

			return nullptr;
		}

		inline std::vector<Shortcut> get_all_shortcut() { return this->shortcut; }

		inline bool exist_shortcut(std::string name)
		{
			for (size_t i = 0; i < this->shortcut.size(); i++)
				if (this->shortcut[i].get_name() == name)
					return true;

			return false;
		}

		bool fail;

	private:
		std::vector<Shortcut> shortcut;


		std::string path;

	};
}