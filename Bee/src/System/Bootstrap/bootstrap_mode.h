#pragma once

#include <string>

#include "bootstrap.h"

namespace bt
{
	enum BootMode
	{
		Default,

		ReadFile,
		InlineCMD
	};

	BootMode get_bt_mode(int argc, char* argv[], size_t& input_index)
	{
		for (size_t i = 0; i < argc; i++)
		{
			if ((std::string)argv[i] == "-rf") {
				input_index = i + 1;
				return ReadFile;
			}

			if ((std::string)argv[i] == "-do") {
				input_index = i + 1;
				return InlineCMD;
			}
		}

		return Default;
	}
}