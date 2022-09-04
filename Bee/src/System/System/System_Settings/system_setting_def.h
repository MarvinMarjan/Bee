#pragma once

#include "../../../Source/Util/itellisense_util.h"
#include "../../../Source/Stream/ostream_clr.h"

#include "setting_types_converts.h"
#include "system_setting.h"

namespace sys
{
	struct Defs
	{
		bool itellisense;

		os::ColorSet caret_color;
		os::ColorSet command_color;
		os::ColorSet quote_color;
		os::ColorSet number_sign_color;
		os::ColorSet dollar_sign_color;
		os::ColorSet hyphen_color;

		std::string initial_path;

		bool disable_error_msg;
		bool disable_warn_msg;
	};

	void set_defs(Defs& defs, sys::System_Settings& settings)
	{
		defs.itellisense = sys::boolstring_to_bool(settings["itellisense"]->get_value());

		defs.caret_color = util::semi_raw_to_color_set(settings["caret_color"]->get_value());
		defs.command_color = util::semi_raw_to_color_set(settings["command_color"]->get_value());
		defs.quote_color = util::semi_raw_to_color_set(settings["quote_color"]->get_value());
		defs.number_sign_color = util::semi_raw_to_color_set(settings["number_sign_color"]->get_value());
		defs.dollar_sign_color = util::semi_raw_to_color_set(settings["dollar_sign_color"]->get_value());
		defs.hyphen_color = util::semi_raw_to_color_set(settings["hyphen_color"]->get_value());

		defs.initial_path = settings["initial_path"]->get_value();

		defs.disable_error_msg = sys::boolstring_to_bool(settings["disable_error_msg"]->get_value());
		defs.disable_warn_msg = sys::boolstring_to_bool(settings["disable_warn_msg"]->get_value());
	}
}