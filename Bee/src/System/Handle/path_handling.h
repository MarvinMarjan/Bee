#pragma once

#include <string>

#include "../Bootstrap/bootstrap.h"


namespace hand
{
	class Path
	{
	public:
		Path(bt::Bootstrap bt) { this->path = bt.get_call_path(); }
		Path(std::string path) { this->path = path; }
		Path() {};

		inline void operator=(std::string path) { this->path = path; }

		inline void set_path(std::string path) { this->path = path; }
		inline std::string get_path() { return this->path; }
		inline std::string get_pathf()
		{
			return this->path + ((this->path[this->path.size() - 1] == '\\' || this->path[this->path.size() - 1] == '/') ? "" : "/");
		}

	private:
		std::string path;
	};
}