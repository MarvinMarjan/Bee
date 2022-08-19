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

	enum ButtonVisible
	{
		True = TRUE,
		False = FALSE
	};

	inline void set_window(WindowState state)
	{
		ShowWindow(GetConsoleWindow(), state);
	}

	inline void set_mouse_visible(ButtonVisible state)
	{
		const CONSOLE_CURSOR_INFO c_info = { 1, state };
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c_info);
	}

	inline bool get_button_state(Button btn, ButtonState state)
	{
		if (state == Pressed) return ((int)GetKeyState(btn) == -127 || (int)GetKeyState(btn) == -128);
		else if (state == Released) return ((int)GetKeyState(btn) != -127 && (int)GetKeyState(btn) != -128);
	}
}