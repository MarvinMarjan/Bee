#pragma once

#include <string>

#include "commands.h"

namespace cmd
{
	enum Command
	{
		Null,
		Not_found,

		Exit,
		Detail,
		Help,
		Clear,

		CD,
		Diagnostic
	};

	class CMD_Data
	{
	public:
		CMD_Data(Command _cmd)
		{
			switch (_cmd)
			{
			case Exit:
				this->name = "exit";
				this->description = "Exit the program";
				this->syntax = "exit";
				break;

			case Detail:
				this->name = "detail";
				this->description = "Show program details (Version, Name)";
				this->syntax = "detail";
				break;

			case Help:
				this->name = "help";
				this->description = "Show this message";
				this->syntax = "help";
				break;

			case Clear:
				this->name = "clear";
				this->description = "Clear the console";
				this->syntax = "clear";
				break;

			case CD:
				this->name = "cd";
				this->description = "Helps with directory navigation";
				this->syntax = "cd [ Path ]";
				break;

			case Diagnostic:
				this->name = "diag";
				this->description = "Displays the details of the current directory";
				this->syntax = "diag [ dirs_size (-ds) ? ] [ path_debug (-pd) ? ] ";
				break;

			default:
				this->name = "<invalid>";
				this->description = "<invalid>";
				this->syntax = "<invalid>";
			}
		}

		std::string name;
		std::string description;
		std::string syntax;
	};

	int arg_size(Command cmd)
	{
		switch (cmd)
		{
		case CD:
			return 1;

		case Diagnostic:
			return 0;

		default:
			return -1;
		}
	}
}