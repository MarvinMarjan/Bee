#pragma once

#include "../../../Source/Util/itellisense_util.h"

#include <string>
#include <vector>

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
				if (util::string_to_color(value) != os::Nothing) return true;
				break;

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

	class System_Settings
	{
	public:
		System_Settings() {
			this->settings = {
				Sys_Setting("itellisense", "true", Bool),
				Sys_Setting("caret_color", "RED", Color)
			};
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

	private:
		std::vector<Sys_Setting> settings;
	};
}