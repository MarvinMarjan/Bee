#pragma once

#include "../Stream/istream.h"

namespace op
{
	enum Operator
	{
		Null,

		OP_Repeat,
		OP_Do
	};

	Operator check(char ch)
	{
		switch ((int)ch)
		{
		case is::Period: return OP_Repeat;
		case is::Colon: return OP_Do;
		default: return Null;
		}
	}
}