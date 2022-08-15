#pragma once

#include <Windows.h>

namespace util
{
	enum Button
	{
		Ctrl = VK_CONTROL
	};

	enum ButtonState
	{
		Pressed,
		Released
	};

	enum WindowState
	{
		Hidden = SW_HIDE,
		Visible = SW_SHOW
	};

	inline void set_window(WindowState state)
	{
		ShowWindow(GetConsoleWindow(), state);
	}

	inline bool get_button_state(Button btn, ButtonState state)
	{
		if (state == Pressed) return ((int)GetKeyState(btn) == -127 || (int)GetKeyState(btn) == -128);
		else if (state == Released) return ((int)GetKeyState(btn) != -127 && (int)GetKeyState(btn) != -128);
	}
}