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
		Diagnostic,
		Print,
		Set,
		Del,
		List,

		Mfile,
		RMfile,
		Mdir,
		RMdir,
		Rename
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
				this->name_variants = { "exit", ".x", ".exit", "quit", ".quit" };
				break;

			case Detail:
				this->name = "detail";
				this->description = "Show program details (Version, Name)";
				this->syntax = "detail";
				this->name_variants = { "detail", ".d", ".detail" };
				break;

			case Help:
				this->name = "help";
				this->description = "Show this message";
				this->syntax = "help";
				this->name_variants = { "help", ".h", ".help" };
				break;

			case Clear:
				this->name = "clear";
				this->description = "Clear the console";
				this->syntax = "clear";
				this->name_variants = { "clear", "clean", ".cl" };
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
				this->name_variants = { "diag", "diagnostic" };
				break;

			case Print:
				this->name = "print";
				this->description = "Print a specific value in the console";
				this->syntax = "print [ String ]";
				break;

			case Set:
				this->name = "set";
				this->description = "Create or edit a shortcut";
				this->syntax = "set [ Name ] [ Value ]";
				break;

			case Del:
				this->name = "del";
				this->description = "Delete a shortcut";
				this->syntax = "del [ Name ]";
				break;

			case List:
				this->name = "list";
				this->description = "List all shortcuts";
				this->syntax = "list";
				break;

			case Mfile:
				this->name = "mfile";
				this->description = "Create a file";
				this->syntax = "mfile [ Path ]";
				this->name_variants = { "mfile", "make_file"};
				break;

			case RMfile:
				this->name = "rmfile";
				this->description = "Remove a file";
				this->syntax = "rmfile [ Path ]";
				this->name_variants = { "rmfile", "remove_file" };
				break;

			case Mdir:
				this->name = "mdir";
				this->description = "Create e directory";
				this->syntax = "mdir [ Path ]";
				this->name_variants = { "mdir", "make_dir" };
				break;

			case RMdir:
				this->name = "rmdir";
				this->description = "Remove a directory";
				this->syntax = "rmdir [ Path ]";
				this->name_variants = { "rmdir", "remove_dir" };
				break;

			case Rename:
				this->name = "rename";
				this->description = "Rename a file/directory";
				this->syntax = "rename [ Path ] [ New_Name ]";
				break;

			default:
				this->name = "<invalid>";
				this->description = "<invalid>";
				this->syntax = "<invalid>";
				this->name_variants = { "<invalid>" };
			}
		}

		std::string name;
		std::string description;
		std::string syntax;
		std::vector<std::string> name_variants;
	};

	int arg_size(Command cmd)
	{
		switch (cmd)
		{
		case CD:         return 1;
		case Diagnostic: return 0;
		case Print:	     return 0;
		case Set:        return 2;
		case Del:        return 1;
		case List:       return 0;

		case Mfile:      return 1;
		case RMfile:     return 1;
		case Mdir:       return 1;
		case RMdir:      return 1;
		case Rename:     return 2;

		default: return -1;
		}
	}
}