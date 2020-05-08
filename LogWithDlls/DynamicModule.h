#pragma once
#include <Windows.h>

#include "..\DllDynamic\DllDynamic.h"

class DynamicModule
{
public:
	static void LoadDynamicDll();
	static void UnloadDynamicDll();
	static IDllDynamic* CreateDynamicObj(const char* title);
};

