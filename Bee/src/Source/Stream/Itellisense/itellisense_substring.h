#pragma once

#include <string>

#include "../../Util/string_util.h"

namespace it
{
	struct substring {
		size_t begin;
		size_t end;
	};

	inline void set_substring(substring& substr, std::string buffer, size_t init_index)
	{
		if (buffer[init_index] == '\"') { 
			substr.begin = util::find_first(buffer, '\"', ((init_index > 1) ? init_index - 1 : init_index), util::Left);
			substr.end = util::find_first(buffer, '\"', init_index, util::Right);
		} else {
			substr.begin = util::find_first(buffer, ' ', init_index, util::Left);
			substr.end = util::find_first(buffer, ' ', init_index, util::Right);
		}
	}
}