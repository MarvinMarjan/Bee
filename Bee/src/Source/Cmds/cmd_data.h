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
		Setting,
		Detail,
		Help,
		Clear,

		Color,
		Color_Mode,
		Errs,
		Warns,

		CD,
		Diagnostic,
		Print,

		Add,
		Rmv,
		Return,

		Set,
		Del,
		List,

		Mfile,
		RMfile,
		Mdir,
		RMdir,
		Rename,
		Sizeof,
		Lineof,
		Read,
		Write,

		Run,
		Stat

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
				this->name_variants = { this->name, ".x", ".exit", "quit", ".quit" };
				break;

			case Setting:
				this->name = "setting";
				this->description = "Show/Edit system settings";
				this->syntax = "setting";
				this->name_variants = { this->name, "config", ".sett", ".conf", "*" };
				break;

			case Detail:
				this->name = "detail";
				this->description = "Show program details (Version, Name)";
				this->syntax = "detail";
				this->name_variants = { this->name, ".d", ".detail" };
				break;

			case Help:
				this->name = "help";
				this->description = "Show this message";
				this->syntax = "help [ Command ? ] { command_name (-cn) ? }";
				this->name_variants = { this->name, ".h", ".help" };
				break;

			case Clear:
				this->name = "clear";
				this->description = "Clear the console";
				this->syntax = "clear";
				this->name_variants = { this->name, "clean", ".cl" };
				break;

			case Color:
				this->name = "color";
				this->description = "Show a list of colors";
				this->syntax = "color";
				this->name_variants = { this->name, "clr" };
				break;

			case Color_Mode:
				this->name = "color_mode";
				this->description = "Show a list of color modes";
				this->syntax = "color_mode";
				this->name_variants = { this->name, "cmode" };
				break;

			case Errs:
				this->name = "errs";
				this->description = "Show a list of system erros";
				this->syntax = "errs";
				this->name_variants = { this->name, "erros", "err" };
				break;

			case Warns:
				this->name = "warns";
				this->description = "Show a list of system warnings";
				this->syntax = "warns";
				this->name_variants = { this->name, "warn" };
				break;

			case CD:
				this->name = "cd";
				this->description = "Helps with directory navigation";
				this->syntax = "cd [ Path ]";
				this->name_variants = { this->name };
				break;

			case Diagnostic:
				this->name = "diag";
				this->description = "Displays the details of the current directory";
				this->syntax = "diag { dirs_size (-ds) ? } { path_debug (-pd) ? } ";
				this->name_variants = { this->name, "diagnostic" };
				break;

			case Print:
				this->name = "print";
				this->description = "Print a specific value in the console";
				this->syntax = "print [ String ]";
				this->name_variants = { this->name };
				break;

			case Add:
				this->name = "add";
				this->description = "Add a new command";
				this->syntax = "add [ Cmd_Name ] [ Block ]";
				this->name_variants = { this->name };
				break;

			case Rmv:
				this->name = "rmv";
				this->description = "Remove a created command";
				this->syntax = "rmv [ Cmd_Name ]";
				this->name_variants = { this->name, "remove" };
				break;

			case Return:
				this->name = "return";
				this->description = "Defines a return value in a function (only works in created functions)";
				this->syntax = "return [ Value ]";
				this->name_variants = { this->name };
				break;

			case Set:
				this->name = "set";
				this->description = "Create or edit a shortcut";
				this->syntax = "set [ Name ] [ Value ]";
				this->name_variants = { this->name };
				break;

			case Del:
				this->name = "del";
				this->description = "Delete a shortcut";
				this->syntax = "del [ Name ]";
				this->name_variants = { this->name };
				break;

			case List:
				this->name = "list";
				this->description = "List all Shortcuts/Functions";
				this->syntax = "list [ Name ? ]";
				this->name_variants = { this->name };
				break;

			case Mfile:
				this->name = "mfile";
				this->description = "Create a file";
				this->syntax = "mfile [ Path ]";
				this->name_variants = { this->name, "make_file"};
				break;

			case RMfile:
				this->name = "rmfile";
				this->description = "Remove a file";
				this->syntax = "rmfile [ Path ]";
				this->name_variants = { this->name, "remove_file" };
				break;

			case Mdir:
				this->name = "mdir";
				this->description = "Create e directory";
				this->syntax = "mdir [ Path ]";
				this->name_variants = { this->name, "make_dir" };
				break;

			case RMdir:
				this->name = "rmdir";
				this->description = "Remove a directory";
				this->syntax = "rmdir [ Path ]";
				this->name_variants = { this->name, "remove_dir" };
				break;

			case Rename:
				this->name = "rename";
				this->description = "Rename a file/directory";
				this->syntax = "rename [ Path ] [ New_Name ]";
				this->name_variants = { this->name };
				break;

			case Sizeof:
				this->name = "sizeof";
				this->description = "Return the size of a file in bytes";
				this->syntax = "sizeof [ Path ]";
				this->name_variants = { this->name };
				break;

			case Lineof:
				this->name = "lineof";
				this->description = "Return the total lines of a file";
				this->syntax = "lineof [ Path ]";
				this->name_variants = { this->name };
				break;

			case Read:
				this->name = "read";
				this->description = "Return the content of a file";
				this->syntax = "read [ Path ]";
				this->name_variants = { this->name, "read_file" };
				break;

			case Write:
				this->name = "write";
				this->description = "Write content in a file";
				this->syntax = "write [ Path ] [ Content ] { clear_file (-cf) ? } { disable_newline (-nl) ? }";
				this->name_variants = { this->name, "write_file" };
				break;

			case Run:
				this->name = "run";
				this->description = "Run a OS command";
				this->syntax = "run [ Command ]";
				this->name_variants = { this->name };
				break;

			case Stat:
				this->name = "stat";
				this->description = "Show OS status";
				this->syntax = "stat { update (-up) ? }";
				this->name_variants = { this->name, "stats", "status", ".s" };
				break;

			default:
				this->name = "<invalid>";
				this->description = "<invalid>";
				this->syntax = "<invalid>";
				this->name_variants = { this->name };
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

		case Add:        return 2;
		case Rmv:        return 1;
		case Return:     return 1;

		case Set:        return 2;
		case Del:        return 1;

		case Mfile:      return 1;
		case RMfile:     return 1;
		case Mdir:       return 1;
		case RMdir:      return 1;
		case Rename:     return 2;
		case Sizeof:     return 1;
		case Lineof:     return 1;

		case Read:       return 1;
		case Write:      return 2;

		case Run:        return 1;

		default: return 0;
		}
	}
}