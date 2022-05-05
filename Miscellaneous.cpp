#include "Miscellaneous.h"

Miscellaneous::Miscellaneous() {}

Miscellaneous::~Miscellaneous() {}

void Miscellaneous::FindAllOccurrences(const std::string& data, const std::string& query, std::vector<size_t>& occurancesPoss) {
	size_t pos = data.find(query);
	while(pos != std::string::npos) {
		occurancesPoss.push_back(pos);
		pos = data.find(query, pos + query.size());
	}
}