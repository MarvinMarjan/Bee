#pragma once

#include "../../../Source/Util/itellisense_util.h"
#include "../../../Source/Stream/ostream_clr.h"

#include "system_setting.h"

namespace sys
{
	struct Defs
	{
		os::Color caret_color;
	};

	void set_defs(Defs& defs, sys::System_Settings& settings)
	{
		defs.caret_color = util::string_to_color(settings["caret_color"]->get_value());
	}
}