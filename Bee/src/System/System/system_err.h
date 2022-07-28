#pragma once

#include <string>

namespace sys
{
	enum ErrorType
	{
		Command_Not_Found,
		Invalid_Path
	};

	class Error
	{
	public:
		Error(ErrorType error)
		{
			switch (error)
			{
			case Command_Not_Found:
				this->name = "Command_Not_Found";
				this->msg = "The following command was write incorrectly or does not exist";
				break;

			case Invalid_Path:
				this->name = "Invalid_Path";
				this->msg = "The following path isn't a folder or does not exist";
				break;
			}
		}

		std::string name;
		std::string msg;
	};
}