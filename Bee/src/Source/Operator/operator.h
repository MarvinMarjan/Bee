#pragma once

namespace op
{
	enum Operator
	{
		Null,

		OP_Repeat
	};

	Operator check(char ch)
	{
		if (ch == '.') return OP_Repeat;

		else return Null;
	}
}