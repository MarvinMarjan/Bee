#pragma once

#include <Windows.h>
#include <direct.h>
#include <iostream>
#include <cstdlib>
#include <string>

#include "../../Source/Stream/ostream_clr.h"

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
			const CONSOLE_CURSOR_INFO c_info = { 1, FALSE };
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c_info);

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