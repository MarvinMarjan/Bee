#pragma once

#include "op_process.h"

namespace op
{
	enum Operator
	{
		Null,

		OP_Repeat
	};

	class OP_Aux
	{
	public:
		op::OP_Repeat_Process repeat;
	};

	Operator check(char ch)
	{
		if (ch == '.') return OP_Repeat;

		else return Null;
	}
}