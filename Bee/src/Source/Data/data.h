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

			for (cmd::CMD_Data command : cmd::commands)
				if (command.predef) this->function.push_back(Function(command.name, {}, true));

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
				if (!sct.predef) this->shortcut_db["shortcut"].push_back({ {"name", sct.get_name()}, {"value", sct.get_value()} });

			for (Function func : this->function)
				if (!func.predef) this->function_db["function"].push_back({ {"name", func.get_name()}, {"block", func.get_block()} });

			util::write_file(BEE_SHORTCUT_FILE_PATH, this->shortcut_db.dump(2), std::ios::out, false);
			util::write_file(BEE_FUNCTION_FILE_PATH, this->function_db.dump(2), std::ios::out, false);
		}

		inline void del_shortcut(std::string name) {
			for (size_t i = 0; i < this->shortcut.size(); i++)
				if (this->shortcut[i].get_name() == name)
					this->shortcut.erase(this->shortcut.begin() + i);
		}

		inline void del_function(std::string name) {
			for (size_t i = 0; i < this->function.size(); i++)
				if (this->function[i].get_name() == name)
					this->function.erase(this->function.begin() + i);
		}

		inline void add_shortcut(Shortcut shortcut) { this->shortcut.push_back(shortcut); }
		inline void add_function(Function function) { this->function.push_back(function); }

		inline Shortcut* get_shortcut(std::string name) {
			for (size_t i = 0; i < this->shortcut.size(); i++)
				if (this->shortcut[i].get_name() == name)
					return &this->shortcut[i];

			return nullptr;
		}

		inline Function* get_function(std::string name) {
			for (size_t i = 0; i < this->function.size(); i++)
				if (this->function[i].get_name() == name)
					return &this->function[i];

			return nullptr;
		}

		inline std::vector<Shortcut> get_all_shortcut() { return this->shortcut; }
		inline std::vector<Function> get_all_function() { return this->function; }

		inline bool exist_shortcut(std::string name) {
			for (size_t i = 0; i < this->shortcut.size(); i++)
				if (this->shortcut[i].get_name() == name)
					return true;

			return false;
		}

		inline bool exist_function(std::string name) {
			for (size_t i = 0; i < this->function.size(); i++)
				if (this->function[i].get_name() == name)
					return true;

			return false;
		}

		inline bool is_predef_function(std::string name) {
			for (size_t i = 0; i < this->function.size(); i++)
				if (this->function[i].get_name() == name)
					return this->function[i].predef;

			return false;
		}

		inline bool is_predef_shortcut(std::string name) {
			for (size_t i = 0; i < this->shortcut.size(); i++)
				if (this->shortcut[i].get_name() == name)
					return this->shortcut[i].predef;

			return false;
		}

		bool fail;

	private:
		std::vector<Shortcut> shortcut =
		{
			Shortcut("NAME", BEE_NAME, true),
			Shortcut("VERSION", BEE_VERSION, true),
			Shortcut("VERSION_STATE", BEE_VERSION_STATE, true),
			Shortcut("OS", BEE_OPERATIONAL_SYSTEM, true)
		};

		std::vector<Function> function;

		json shortcut_db;
		json function_db;

		std::string stc_path;
		std::string func_path;
	};
}