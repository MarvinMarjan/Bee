#pragma once

#include <string>

namespace sys
{
	enum ErrorType
	{
		Command_Not_Found
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
			}
		}

		std::string name;
		std::string msg;
	};
}