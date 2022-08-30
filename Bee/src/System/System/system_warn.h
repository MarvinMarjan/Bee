#pragma once

#include <string>

namespace sys
{
	enum WarnType
	{
		DataBase_Bootstrap_Err,
		Settings_Bootstrap_Err,

		Incomplete_Expression,
		Shortcut_Not_Found_Warn,
		Insufficient_Args
	};

	class Warning
	{
	public:
		Warning(WarnType warn)
		{
			switch (warn)
			{
			case DataBase_Bootstrap_Err:
				this->name = "DataBase_Bootstrap_Err";
				this->msg = "Couldn't initialize DataBase. Data can't be saved";
				break;

			case Settings_Bootstrap_Err:
				this->name = "Settings_Bootstrap_Err";
				this->msg = "Couldn't initialize Settings. Using default Settings";
				break;

			case Insufficient_Args:
				this->name = "Insufficient_Args";
				this->msg = "The past arguments are insufficient";
				break;

			case Incomplete_Expression:
				this->name = "Incomplete_Expression";
				this->msg = "Incomplete Expression";
				break;

			case Shortcut_Not_Found_Warn:
				this->name = "Shortcut_Not_Found";
				this->msg = "The following shortcut couldn't be found";
				break;

			default:
				this->name = "<invalid>";
				this->msg = "<invalid>";
				break;
			}
		}

		std::string name;
		std::string msg;
	};
}