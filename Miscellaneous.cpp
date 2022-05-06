#include "Miscellaneous.hpp"

bool Miscellaneous::isCOMInitialized = false;

Miscellaneous::Miscellaneous() {
	if(!isCOMInitialized) {
		HRESULT handleResult = CoInitialize(nullptr);

		if(SUCCEEDED(handleResult)) {
			isCOMInitialized = true;
		}
	}
}

Miscellaneous::~Miscellaneous() {
	if(isCOMInitialized) {
		CoUninitialize();

		isCOMInitialized = false;
	}
}

void Miscellaneous::FindAllOccurrences(const std::string& data, const std::string& query, std::vector<size_t>& occurancesPoss) {
	size_t pos = data.find(query);
	while(pos != std::string::npos) {
		occurancesPoss.push_back(pos);
		pos = data.find(query, pos + query.size());
	}
}

void Miscellaneous::GetFilesInDirectory(const std::string& directory, std::vector<std::string>& files) {
	HANDLE handleDirectory;
	WIN32_FIND_DATAA findData;

	handleDirectory = FindFirstFileA((directory + "/*").c_str(), &findData);
	if(handleDirectory == INVALID_HANDLE_VALUE) {
		return;
	}

	do {
		if(findData.cFileName[0] == '.' ||
		   findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			continue;
		}

		files.push_back(directory + "\\" + findData.cFileName);
	} while(FindNextFileA(handleDirectory, &findData));

	FindClose(handleDirectory);
}

std::string Miscellaneous::GetShortcutTarget(const std::string& shortcut) {
	IShellLinkA* pisl = nullptr;
	std::string target(MAX_PATH, ' ');
	std::wstring path(shortcut.begin(), shortcut.end());

	HRESULT handleResult = CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_IShellLinkA, (LPVOID*)&pisl);
	if(SUCCEEDED(handleResult)) {

		IPersistFile* pipf = nullptr;
		handleResult = pisl->QueryInterface(IID_IPersistFile, (LPVOID*)&pipf);
		if(SUCCEEDED(handleResult)) {

			handleResult = pipf->Load(path.c_str(), STGM_READ);
			if(SUCCEEDED(handleResult)) {
				WIN32_FIND_DATAA findData { 0 };
				pisl->GetPath(&target[0], MAX_PATH, &findData, SLGP_UNCPRIORITY | SLGP_RAWPATH);
			}

			pipf->Release();
		}

		pisl->Release();
	}

	return target;
}

void Miscellaneous::GetAllShortcutsTargetFromDesktop(std::vector<std::string>& files) {
	char pathDirectory[MAX_PATH] = { 0 };
	SHGetSpecialFolderPathA(HWND_DESKTOP, pathDirectory, CSIDL_DESKTOP, false);

	GetFilesInDirectory(pathDirectory, files);
	files.erase(std::remove_if(files.begin(), files.end(), [] (const std::string& file) { return file.substr(file.length() - 4) != ".lnk"; }), files.end());
	std::for_each(files.begin(), files.end(), [&] (std::string& file) { file = GetShortcutTarget(file); });
}

std::string Miscellaneous::SHA256(const std::string& text) {
	static char salt[17] = { 0 };
	char textWithSalt[64] = { 0 };

	HCRYPTPROV hCryptProv = 0;
	HCRYPTHASH hCryptHash = 0;

	strcat_s(textWithSalt, text.c_str());
	strcat_s(textWithSalt, salt);

	if(!CryptAcquireContextA(&hCryptProv, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
		return "";
	}

	if(!CryptCreateHash(hCryptProv, CALG_SHA_256, 0, 0, &hCryptHash)) {
		CryptReleaseContext(hCryptProv, 0);

		return "";
	}

	if(!CryptHashData(hCryptHash, (uint8_t*)textWithSalt, (uint32_t)strlen(textWithSalt), 0)) {
		CryptDestroyHash(hCryptHash);
		CryptReleaseContext(hCryptProv, 0);

		return "";
	}

	unsigned long hashSize = 32;
	uint8_t hashBytes[32] = { 0 };

	if(!CryptGetHashParam(hCryptHash, HP_HASHVAL, hashBytes, &hashSize, 0)) {
		CryptDestroyHash(hCryptHash);
		CryptReleaseContext(hCryptProv, 0);

		return "";
	}

	const char* hex = "0123456789ABCDEF";
	char hashString[65] = { 0 };

	for(size_t i = 0; i < 32; i++) {
		hashString[i * 2] = hex[hashBytes[i] >> 4];
		hashString[i * 2 + 1] = hex[hashBytes[i] & 0xF];
	}

	CryptDestroyHash(hCryptHash);
	CryptReleaseContext(hCryptProv, 0);

	return hashString;
}

std::string Miscellaneous::System(const std::string& command) {
	std::string output;

	FILE* pPipe;
	if(!(pPipe = _popen(command.c_str(), "rt"))) {
		output = "Failed to run command\n";

		return output;
	}

	char psBuffer[128];
	while(fgets(psBuffer, 128, pPipe)) {
		output += psBuffer + '\n';
	}

	if(feof(pPipe)) {
		output += "\nProcess returned " + _pclose(pPipe) + '\n';
	} else {
		output += "Error: Failed to read the pipe to the end.\n";
	}

	return output;
}