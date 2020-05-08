// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <cstdlib>
#include <ctime>

#include "..\SingletonLog\SingletonLog.h"

using namespace std;

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		_log.info("Dll Static (DLL_PROCESS_ATTACH)");
		std::srand((unsigned int)std::time(nullptr));
		break;

	case DLL_THREAD_ATTACH:
		_log.info("Dll Static (DLL_THREAD_ATTACH)");
		std::srand((unsigned int)std::time(nullptr));
		break;

	case DLL_THREAD_DETACH:
		_log.info("Dll Static (DLL_THREAD_DETACH)");
		break;

	case DLL_PROCESS_DETACH:
		_log.info("Dll Static (DLL_PROCESS_DETACH)");
		break;

	}
	return TRUE;
}

