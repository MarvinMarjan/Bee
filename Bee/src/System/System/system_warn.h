#pragma once

#include <string>

namespace sys
{
	enum WarnType
	{
		Insufficient_Args
	};

	class Warning
	{
	public:
		Warning(WarnType warn)
		{
			switch (warn)
			{
			case Insufficient_Args:
				this->name = "Insufficient_Args";
				this->msg = "The past arguments are insufficient";
				break;
			}
		}

		std::string name;
		std::string msg;
	};
}