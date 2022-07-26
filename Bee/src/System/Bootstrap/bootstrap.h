#pragma once

#include <direct.h>
#include <iostream>
#include <string>

#include "../../Source/Stream/ostream_clr.h"
#include "../System/system.h"

namespace bt
{
	inline std::string get_call_path();

	class Bootstrap
	{
	public:
		Bootstrap()
		{
			this->call_path = bt::get_call_path();
		}

		inline std::string get_call_path() { return this->call_path; }

	private:
		std::string call_path;
	};

	inline std::string get_call_path()
	{
		char buff[2048];

		return _getcwd(buff, 2048);
	}
}