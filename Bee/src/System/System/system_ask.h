#pragma once

#include <string>

namespace sys
{
	enum AskType
	{
		Remove_Not_Empty_Dir,
		Replace_File
	};

	class Question
	{
	public:
		Question(AskType question)
		{
			switch (question)
			{
			case Remove_Not_Empty_Dir:
				this->name = "Remove_Not_Empty_Dir";
				this->msg = "The dir isn't empty, do you want to remove it anyway?";
				break;

			case Replace_File:
				this->name = "Replace_File";
				this->msg = "The specified file already exists, would you like to replace it?";
				break;
			}
		}

		std::string name;
		std::string msg;
	};
}