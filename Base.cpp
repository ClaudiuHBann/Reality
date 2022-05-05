#include "Base.hpp"

#ifdef _WIN32

bool Base::IsWSAInitialized() {
	SOCKET newSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(newSocket == INVALID_SOCKET) {
		return false;
	}

	CLOSE_SOCKET(newSocket);
	return true;
}

WSADATA* Base::CreateWSADATAPointer() {
	WSADATA* newWsadata = new WSADATA;
	memset(newWsadata, 0, sizeof(*newWsadata));

	int iResult = WSAStartup(MAKEWORD(2, 2), newWsadata);
	if(iResult != 0) {
		PrintError("Failed to initialize windows sockets api! Error: " + std::to_string(iResult));
	}

	return newWsadata;
}

WSADATA Base::CreateWSADATA() {
	WSADATA newWsadata;
	memset(&newWsadata, 0, sizeof(newWsadata));

	int iResult = WSAStartup(MAKEWORD(2, 2), &newWsadata);
	if(iResult != 0) {
		PrintError("Failed to initialize windows sockets api! Error: " + std::to_string(iResult));
	}

	return newWsadata;
}

#endif

sockaddr_in* Base::CreateSockAddrInPointer(const unsigned long addr, const int family, const unsigned short port) {
	sockaddr_in* newSin = new sockaddr_in;
	memset(newSin, 0, sizeof(*newSin));

	newSin->sin_addr.s_addr = addr;
	newSin->sin_family = family;
	newSin->sin_port = htons(port);

	return newSin;
}

sockaddr_in Base::CreateSockAddrIn(const unsigned long addr, const int family, const unsigned short port) {
	sockaddr_in newSin;
	memset(&newSin, 0, sizeof(newSin));

	newSin.sin_addr.s_addr = addr;
	newSin.sin_family = family;
	newSin.sin_port = htons(port);

	return newSin;
}

SOCKET Base::CreateSocket(const int af, const int type, const int protocol) {
#ifdef _WIN32

	if(!Base::IsWSAInitialized()) {
		Base::CreateWSADATA();
	}

#endif

	SOCKET s = socket(af, type, protocol);
	if(s == INVALID_SOCKET) {
		Base::PrintError("Failed on creating the socket! Error: " + std::to_string(errnum));
	}

	return s;
}
