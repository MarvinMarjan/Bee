#pragma once

#include "../../../Deps/nlohmann/json.hpp"

#include "../../../Source/Util/itellisense_util.h"
#include "../../../Source/Util/filesys_util.h"

#include <string>
#include <vector>


#define BEE_SYSTEM_SETTINGS_DATA_PATH "src/System/System/system_settings_data.json"

using json = nlohmann::json;

namespace sys
{
	enum SettingType
	{
		Any,
		Color,
		String,
		Integer,
		Float,
		Bool
	};

	std::string type_to_string(SettingType type)
	{
		switch (type)
		{
		case Any:     return "Any";
		case Color:   return "Color";
		case String:  return "String";
		case Integer: return "Integer";
		case Float:   return "Float";
		case Bool:    return "Bool";
		}

		return "Null";
	}

	SettingType string_to_type(std::string type)
	{
		if (type == "Any")	        return Any;
		else if (type == "Color")   return Color;
		else if (type == "String")  return String;
		else if (type == "Integer") return Integer;
		else if (type == "Float")   return Float;
		else if (type == "Bool")    return Bool;

		return Any;
	}

	class Sys_Setting
	{
	public:
		Sys_Setting(std::string name, std::string value, SettingType type) {
			this->name = name;
			this->value = value;
			this->type = type;
		}

		inline void operator=(std::string value) { this->set_value(value); }
		inline void set_value(std::string value) { this->value = value;	}

		
		inline std::string get_value() { return this->value; }
		inline std::string get_name() { return this->name; }
		inline SettingType get_type() { return this->type; }


		bool is_same_type(std::string value)
		{
			switch (this->type)
			{
			case Any: return true;
			case Color:
				if (value[0] == '\\') return true;
				break;

			case String: return true;

			case Bool:
				if (util::to_lower(value) == "true" || util::to_lower(value) == "false") return true;
				break;
			}

			return false;
		}

	private:
		std::string name;
		std::string value;
		SettingType type;
	};


	const std::vector<Sys_Setting> default_settings =
	{
		Sys_Setting("itellisense", "true", Bool),

		Sys_Setting("caret_color", "\\RED;UNDERLINE", Color),
		Sys_Setting("command_color", "\\GRAY;ITALIC", Color),
		Sys_Setting("quote_color", "\\GREEN;NORMAL", Color),
		Sys_Setting("number_sign_color", "\\WT_CYAN;NORMAL", Color),
		Sys_Setting("dollar_sign_color", "\\CYAN;NORMAL", Color),
		Sys_Setting("hyphen_color", "\\YELLOW;DARK", Color),
		Sys_Setting("curly_brace_color", "\\WHITE;DARK", Color),

		Sys_Setting("initial_path", "", String),

		Sys_Setting("disable_error_msg", "false", Bool),
		Sys_Setting("disable_warn_msg", "false", Bool)
	};



	class System_Settings
	{
	public:
		System_Settings() {
			if (!hand::exist_file(BEE_SYSTEM_SETTINGS_DATA_PATH)) {
				this->fail = true;
				return;
			}

			else this->fail = false;

			for (sys::Sys_Setting setting : default_settings)
				this->settings.push_back(setting);

			json data = json::parse(util::read_fs_file(BEE_SYSTEM_SETTINGS_DATA_PATH));

			for (size_t i = 0; i < this->settings.size(); i++) {
				json val = data["settings"][this->settings[i].get_name()]["value"];
				if (!val.is_null()) this->settings[i].set_value(val);
			}
		}

		~System_Settings() {
			if (this->fail) return;

			json data = json::parse(util::read_fs_file(BEE_SYSTEM_SETTINGS_DATA_PATH));

			for (Sys_Setting setting : this->settings)
				data["settings"][setting.get_name()] = json::object({ {"value", setting.get_value()}, {"type", type_to_string(setting.get_type())}});

			util::write_file(BEE_SYSTEM_SETTINGS_DATA_PATH, data.dump(2), std::ios::out);
		}

		inline void set_default_settings(std::vector<Sys_Setting> default_settings) {
			this->settings = default_settings;
		}

		inline std::vector<Sys_Setting> get_all() { return this->settings; }

		inline size_t get_size() { return this->settings.size(); }
		
		inline Sys_Setting* operator[](std::string setting_name) {
			for (size_t i = 0; i < this->settings.size(); i++)
				if (this->settings[i].get_name() == setting_name)
					return &this->settings[i];

			return nullptr;
		}

		inline Sys_Setting* operator[](size_t index) { return &this->settings[index]; }


		inline bool exist(std::string name) {
			for (Sys_Setting setting : this->settings)
				if (setting.get_name() == name)
					return true;

			return false;
		}

		inline bool exist(size_t index) {
			if (index < this->get_size()) return true;

			return false;
		}

		bool fail;

	private:
		std::vector<Sys_Setting> settings;
	};




	
}