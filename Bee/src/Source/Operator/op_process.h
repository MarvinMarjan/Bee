#pragma once

#include "OP_Repeat/op_iterator.h"

namespace op
{
	class OP_Repeat_Process
	{
	public:
		OP_Repeat_Process() {};
		OP_Repeat_Process(size_t times) { this->times = times; }

		op::Iterator times;
		op::Iterator itr;

		bool is = false;
	};
}