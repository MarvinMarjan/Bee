#pragma once

#include <Windows.h>
#include <direct.h>
#include <iostream>
#include <cstdlib>
#include <string>

#include "../../Source/Stream/ostream_clr.h"
#include "../../Source/Util/system_util.h"

namespace bt
{
	inline std::string get_call_path();

	class Bootstrap
	{
	public:
		Bootstrap()
		{
			this->call_path = bt::get_call_path();

			// disable console caret
			util::set_mouse_visible(util::False);

			system("color");
		}

		inline std::string get_call_path() { return this->call_path; }

		std::vector<std::string> src_file;

	private:
		std::string call_path;
		std::string local_app_path;

	};

	inline std::string get_call_path()
	{
		char buff[2048];

		return _getcwd(buff, 2048);
	}
}