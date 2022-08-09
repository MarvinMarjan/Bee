#pragma once

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
			//this->local_app_path = ((!("BEE_PATH")) ? "NULL" : _wgetenv("BEE_PATH"));
		}

		inline std::string get_call_path() { return this->call_path; }
		//inline std::string get_local_app_path() { return this->local_app_path; }

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