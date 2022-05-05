#pragma once

#include <Windows.h>

#include <string>
#include <vector>

class Clipboard {
public:
	Clipboard();
	~Clipboard();

	inline std::string GetDataAsString() {
		std::string text("");
		GetData(CF_TEXT, &text);
		return text;
	}

	inline std::wstring GetDataAsStringWide() {
		std::wstring text(L"");
		GetData(CF_UNICODETEXT, &text);
		return text;
	}

	/*
		Clipboard Formats: https://docs.microsoft.com/en-us/windows/win32/dataxchg/standard-clipboard-formats

		Understandable Clipboard Formats
	*/
	static std::vector<uint32_t> m_types;

private:
	void GetData(uint16_t format, void* dataDestination);
};