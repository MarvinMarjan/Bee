#pragma once

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
		if (ch == '.') return OP_Repeat;
		else if (ch == ':') return OP_Do;

		else return Null;
	}
}