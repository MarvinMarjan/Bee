#pragma once

#include <string>

#include "system_setting.h"

namespace sys
{
	inline bool boolstring_to_bool(std::string value)
	{
		if (value == "true") return true;
		else if (value == "false") return false;

		return false;
	}
}