#pragma once

#include <string>
#include <vector>

namespace sys
{
	enum ErrorType
	{
		Type_Conversion_Err,

		Base_Function_Not_Found,
		Function_Not_Found_Err,
		Shortcut_Not_Found_Err,
		Setting_Not_Found_Err,
		Command_Not_Found,

		Invalid_Path_File,
		Invalid_Path_Dir,

		Unavaliable_Name
	};

	class Error
	{
	public:
		Error(ErrorType error)
		{
			switch (error)
			{
			case Type_Conversion_Err:
				this->name = "Type_Conversion_Err";
				this->msg = "Type conversion error";
				break;

			case Base_Function_Not_Found:
				this->name = "Base_Function_Not_Found";
				this->msg = "The following base function couldn't be found";
				break;

			case Function_Not_Found_Err:
				this->name = "Function_Not_Found";
				this->msg = "The following function couldn't be found";
				break;

			case Shortcut_Not_Found_Err:
				this->name = "Shortcut_Not_Found";
				this->msg = "The following shortcut couldn't be found";
				break;
				
			case Setting_Not_Found_Err:
				this->name = "Setting_Not_Found";
				this->msg = "The following setting couldn't be found";
				break;

			case Command_Not_Found:
				this->name = "Command_Not_Found";
				this->msg = "The following command was write incorrectly or does not exist";
				break;

			case Invalid_Path_File:
				this->name = "Invalid_Path_File";
				this->msg = "The following path isn't a file or does not exist";
				break;

			case Invalid_Path_Dir:
				this->name = "Invalid_Path_Dir";
				this->msg = "The following path isn't a folder or does not exist";
				break;

			case Unavaliable_Name:
				this->name = "Unavaliable_Name";
				this->msg = "The following name is unavaliable";
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