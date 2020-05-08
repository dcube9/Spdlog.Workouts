#include "stdafx.h"

#include "..\SingletonLog\SingletonLog.h"

#include "DynamicModule.h"

using namespace std;

static HINSTANCE hdDD = NULL;
static FactoryDllDynamic_f funDD = nullptr;

void DynamicModule::LoadDynamicDll()
{
	_log.info("*** Before load dll dynamic");
	hdDD = LoadLibrary("DllDynamic.dll");
	funDD = (FactoryDllDynamic_f)(GetProcAddress(hdDD, "FactoryDllDynamic"));
}

void DynamicModule::DynamicModule::UnloadDynamicDll()
{
	if (hdDD != nullptr)
		FreeLibrary(hdDD);

	hdDD = nullptr;
	_log.info("*** After unload dll dynamic");
}

IDllDynamic* DynamicModule::CreateDynamicObj(const char* title)
{
	return (*funDD)(title);
}
