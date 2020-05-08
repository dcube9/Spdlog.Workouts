// LogWithDlls.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <windows.h>
#include <string>

#include "..\DllStatic\DllStatic.h"
#include "..\DllDynamic\DllDynamic.h"
#include "..\SingletonLog\SingletonLog.h"

#include "DynamicModule.h"
#include "Utilities.h"

using namespace std;

shared_ptr<CDllStatic> objStatic4(new CDllStatic("Call from : MAIN - Heap in global"));
CDllStatic objStatic3("Call from : MAIN - Stack in global");

int main()
{
	_log.info("*** Main() - First line");

	shared_ptr<CDllStatic> objStatic1(new CDllStatic("Call from : Main() - Heap"));
	CDllStatic objStatic2("Call from : Main() - Stack");

	DynamicModule::LoadDynamicDll();
	shared_ptr<IDllDynamic> objStatic5(DynamicModule::CreateDynamicObj("Main() - Heap"));
	objStatic5->PrintOut("Hello World !");
	objStatic5 = nullptr;
	DynamicModule::UnloadDynamicDll();

	cout << "*** Press any ENTER to exit";
	std::getchar();

	_log.info("*** Main() - Last line");
	return 0;
}

