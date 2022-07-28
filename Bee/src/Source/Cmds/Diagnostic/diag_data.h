#pragma once

#include "../../Util/filesys_util.h"

#include <string>

namespace cmd
{
	class Diag_data
	{
	public:
		Diag_data(std::string name, util::EntType type, std::string s_type, float byte_size, float size, std::string size_sufix)
		{
			this->name = name;
			this->s_type = s_type;
			this->ent_type = type;

			this->byte_size = byte_size;
			this->size = size;
			this->size_sufix = size_sufix;
		}

		std::string name;
		std::string s_type;

		util::EntType ent_type;

		float size;
		float byte_size;
		std::string size_sufix;
	};
}