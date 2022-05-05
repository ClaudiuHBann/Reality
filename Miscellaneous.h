#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <chrono>

class Miscellaneous {
public:
	Miscellaneous();
	~Miscellaneous();

	static inline void FileAsString(const std::string& file, std::string& str, const std::ios_base::openmode iosOM = std::ios::binary) {
		if(!FileExists(file)) {
			return;
		}

		std::ifstream ifs(file, iosOM);
		str.assign((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	}

	static inline bool FileExists(const std::string& file) {
		struct stat buffer;
		return !stat(file.c_str(), &buffer);
	}

	static inline int64_t TSAsLL() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	static void FindAllOccurrences(const std::string& data, const std::string& query, std::vector<size_t>& occurancesPoss);
};