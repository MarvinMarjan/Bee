#pragma once

#include <string>

namespace sys
{
	enum WarnType
	{
		Incomplete_Expression,
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

			case Incomplete_Expression:
				this->name = "Incomplete_Expression";
				this->msg = "Incomplete Expression";
				break;

			default:
				this->name = "<invalid>";
				this->msg = "<invalid>";
				break;
			}
		}

		std::string name;
		std::string msg;
	};
}