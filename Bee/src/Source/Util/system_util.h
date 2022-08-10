#pragma once

#include <Windows.h>

namespace util
{
	enum WindowState
	{
		Hidden = SW_HIDE,
		Visible = SW_SHOW
	};

	inline void set_window(WindowState state)
	{
		ShowWindow(GetConsoleWindow(), state);
	}
}