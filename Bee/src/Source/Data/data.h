#pragma once

#include "../../Deps/nlohmann/json.hpp"

#include "../Util/filesys_util.h"
#include "../Util/string_util.h"

#include "../../System/System/System_Settings/system_setting.h"

#include "Shortcut/shortcut.h"
#include "Function/function.h"

#include <string>
#include <vector>

#define BEE_SHORTCUT_FILE_PATH "src/Source/Data/DBase/shortcuts.json"
#define BEE_FUNCTION_FILE_PATH "src/Source/Data/DBase/functions.json"

using json = nlohmann::json;

namespace dt
{
	class DBase
	{
	public:
		DBase()
		{
			if (!hand::exist_file(BEE_SHORTCUT_FILE_PATH) || !hand::exist_file(BEE_FUNCTION_FILE_PATH)) {
				this->fail = true;
				return;
			}

			this->shortcut_db = json::parse(util::read_fs_file(BEE_SHORTCUT_FILE_PATH));
			this->function_db = json::parse(util::read_fs_file(BEE_FUNCTION_FILE_PATH));

			for (size_t i = 0; i < this->shortcut_db["shortcut"].size(); i++)
				this->add_shortcut(Shortcut(this->shortcut_db["shortcut"][i]["name"], this->shortcut_db["shortcut"][i]["value"]));

			for (size_t i = 0; i < this->function_db["function"].size(); i++)
				this->add_function(Function(this->function_db["function"][i]["name"], this->function_db["function"][i]["block"]));

			this->fail = false;
		}

		~DBase()
		{
			this->shortcut_db["shortcut"].clear();
			this->function_db["function"].clear();

			for (Shortcut sct : this->shortcut)
				this->shortcut_db["shortcut"].push_back({ {"name", sct.get_name()}, {"value", sct.get_value()} });

			for (Function func : this->function)
				this->function_db["function"].push_back({ {"name", func.get_name()}, {"block", func.get_block()} });

			util::write_file(BEE_SHORTCUT_FILE_PATH, this->shortcut_db.dump(2), std::ios::out, false);
			util::write_file(BEE_FUNCTION_FILE_PATH, this->function_db.dump(2), std::ios::out, false);
		}

		inline void del_shortcut(std::string name)
		{
			for (size_t i = 0; i < this->shortcut.size(); i++)
				if (this->shortcut[i].get_name() == name)
					this->shortcut.erase(this->shortcut.begin() + i);
		}

		inline void del_function(std::string name)
		{
			for (size_t i = 0; i < this->function.size(); i++)
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

		json shortcut_db;
		json function_db;

		std::string stc_path;
		std::string func_path;
	};
}