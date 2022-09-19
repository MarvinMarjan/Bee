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
		Get_Setting,

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
		Stat,

		Kpress,

		If,
		Else,
		While
	};

	class CMD_Data
	{
	public:
		CMD_Data(Command cmd)
		{
			this->adress = cmd;

			switch (cmd)
			{
			case Exit:
				this->set_data("exit", "Exit the program", { ".x", ".exit", "quit", ".quit" });
				break;

			case Setting:
				this->set_data("setting", "Show/Edit system settings", { "config", ".sett", ".conf", "*" }, "setting [ Setting_Name ? ] [ Setting_Value ? ]");
				break;

			case Get_Setting:
				this->set_data("get_setting", "Return the value of a setting", {}, "get_setting [ Setting ]", true);
				break;

			case Detail:
				this->set_data("detail", "Show program details (Version, Name)", { ".d", ".detail" });
				break;

			case Help:
				this->set_data("help", "Show this message", { ".h", ".help" }, "help [ Command ? ] { command_name (-cn) ? }");
				break; 

			case Clear:
				this->set_data("clear", "Clear the console", { "clean", ".cl" });
				break;

			case Color:
				this->set_data("color", "Show a list of colors", { "clr" });
				break;

			case Color_Mode:
				this->set_data("color_mode", "Show a list of color modes", { "cmode" });
				break;

			case Errs:
				this->set_data("errs", "Show a list of system erros", { "erros", "err" });
				break;

			case Warns:
				this->set_data("warns", "Show a list of system warnings", { "warn" });
				break;

			case CD:
				this->set_data("cd", "Helps with directory navigation", {}, "cd [ Path ]");
				break;

			case Diagnostic:
				this->set_data("diag", "Displays the details of the current directory", { "diagnostic" }, "diag { dirs_size (-ds) ? } { path_debug (-pd) ? } ");
				break;

			case Print:
				this->set_data("print", "Print a specific value in the console", {}, "print [ Values... ? ]");
				break;

			case Add:
				this->set_data("add", "Add a new command", {}, "add [ Cmd_Name ] [ Block ]");
				break;

			case Rmv:
				this->set_data("rmv", "Remove a created command", { "remove" }, "rmv [ Cmd_Name ]");
				break;

			case Return:
				this->set_data("return", "Defines a return value in a function (only works in created functions)", {}, "return [ Value ]");
				break;

			case Set:
				this->set_data("set", "Create or edit a shortcut", {}, "set [ Name ] [ Value ]");
				break;

			case Del:
				this->set_data("del", "Delete a shortcut", {}, "del [ Name ]");
				break;

			case List:
				this->set_data("list", "List all Shortcuts/Functions", {}, "list [ Name ]");
				break;

			case Mfile:
				this->set_data("mfile", "Create a file", { "make_file" }, "mfile [ Path ]");
				break;

			case RMfile:
				this->set_data("rmfile", "Remove a file", { "remove_file" }, "rmfile [ Path ]");
				break;

			case Mdir:
				this->set_data("mdir", "Create a directory", { "make_dir" }, "mdir [ Path ]");
				break;

			case RMdir:
				this->set_data("rmdir", "Remove a directory", { "remove_dir" }, "rmdir [ Path ]");
				break;

			case Rename:
				this->set_data("rename", "Rename a file/directory", {}, "rename [ Path ] [ New_Name ]");
				break;

			case Sizeof:
				this->set_data("sizeof", "Return the size of a file in bytes", {}, "sizeof [ Path ]", true);
				break;

			case Lineof:
				this->set_data("lineof", "Return the total lines of a file", {}, "lineof [ Path ]", true);
				break;

			case Read:
				this->set_data("read", "Return the content of a file", { "read_file" }, "read [ Path ]", true);
				break;

			case Write:
				this->set_data("write", "Write content in a file", { "write_file" }, "write [ Path ] [ Content ] { clear_file(-cf) ? } { disable_newline(-nl) ? }");
				break;

			case Run:
				this->set_data("run", "Run a OS command", {}, "run [ Command ]");
				break;

			case Stat:
				this->set_data("stat", "Show OS status", {"stats", "status", ".s"}, "stat { update (-up) ? }");
				break;

			case Kpress:
				this->set_data("kpress", "Return the pressed key", {}, "", true);
				break;

			case If:
				this->set_data("if", "If statement", {}, "if [ Condition ] [ Block ]", false, true);
				break;

			case Else:
				this->set_data("else", "Else statement", {}, "else [ Block ]", false, true);
				break;

			case While:
				this->set_data("while", "While statement", {}, "while [ Condition ] [ Block ]", false, true);
				break;

			default: this->set_data("<invalid>", "<invalid>");
			}
		}

		std::string name;
		std::string description;
		std::string syntax;
		std::vector<std::string> name_variants;

		Command adress;

		bool predef = false;
		bool instruction = false;

	private:
		inline void set_data(std::string name, std::string description, std::vector<std::string> name_variants = {}, std::string syntax = "", bool predef = false, bool instruction = false) {
			if (syntax == "") syntax = name;
			
			this->name = name;
			this->description = description;
			this->syntax = syntax;

			this->name_variants = name_variants;
			this->name_variants.insert(this->name_variants.begin(), name);

			this->predef = predef;
			this->instruction = instruction;
		}
	};

	int arg_size(Command cmd)
	{
		switch (cmd)
		{
		case Get_Setting: return 1;
						  
		case CD:          return 1;
						  
		case Add:         return 2;
		case Rmv:         return 1;
		case Return:      return 1;
						  
		case Set:         return 2;
		case Del:         return 1;
						  
		case Mfile:       return 1;
		case RMfile:      return 1;
		case Mdir:        return 1;
		case RMdir:       return 1;
		case Rename:      return 2;
		case Sizeof:      return 1;
		case Lineof:      return 1;
						  
		case Read:        return 1;
		case Write:       return 2;
						  
		case Run:         return 1;

		case If:          return 2;
		case Else:        return 1;
		case While:       return 2;

		default: return 0;
		}
	}
}