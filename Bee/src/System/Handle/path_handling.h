#pragma once

#include <dirent.h>
#include <string>

#include "../Bootstrap/bootstrap.h"
#include "../../Source/Util/string_util.h"

#include "../../Source/Cmds/cmd_args.h"


namespace hand
{
	inline bool is_abs(std::string path);


	class Path
	{
	public:
		Path(bt::Bootstrap bt) { this->path = bt.get_call_path(); }
		Path(std::string path) { this->path = path; }
		Path() {};

		inline void operator=(std::string path) { this->path = path; }
		inline std::string operator+(std::string another) { return ((!is_abs(another)) ? this->get_pathf() + another : another); }
		inline std::string operator+(cmd::Arg another) { return ((!is_abs(another.get_arg())) ? this->get_pathf() + another.get_arg() : another.get_arg()); }

		inline void set_path(std::string path) { this->path = path; }
		inline std::string get_path() { return this->path; }
		inline std::string get_pathf()
		{
			return this->path + ((this->path[this->path.size() - 1] == '\\' || this->path[this->path.size() - 1] == '/') ? "" : "/");
		}

		void cd(std::string path) 
		{
			if (path == ".") return;
			if (path == "/")
			{
				this->path = "C:/";
				return;
			}

			if (path == "..")
			{
				this->path = util::erase(this->path, util::find_last(this->path, '/'));

				if (this->path == "C:")
					this->path = "C:/";
				return;
			}

			if (is_abs(path))
			{
				this->path = path;
				return;
			}

			while (util::starts_with(path, ".") || util::starts_with(path, "/")) path = util::erase_first(path);

			this->path = this->get_pathf() + path;
		}

	private:
		std::string path;
	};

	inline bool exist_folder(std::string path)
	{
		DIR* dir = opendir(path.c_str());

		return ((!dir) ? false : true);
	}

	inline bool is_abs(std::string path)
	{
		return (util::starts_with(path, "C:/") || util::starts_with(path, "D:/"));
	}
}