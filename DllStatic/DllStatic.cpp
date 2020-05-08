// DllStatic.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include <stdio.h>
#include <cstdlib>
#include <memory>

#include "DllStatic.h"

#include "..\SingletonLog\SingletonLog.h"

using namespace std;

CDllStatic objStatic3("Call from : Dll Static - Stack in global");
shared_ptr<CDllStatic> objStatic4(new CDllStatic("Call from : Dll Static - Heap in global"));

unsigned int GetOneMagicNumber(unsigned int max) // from 1 to max
{
	unsigned int x = max + 1;

	while (x > max)
		x = 1 + std::rand() / ((RAND_MAX + 1u) / max);  // Note: 1+rand()%6 is biased

	return x;
}

// This is the constructor of a class that has been exported.
// see DllStatic.h for the class definition
CDllStatic::CDllStatic(const char* title)
{
	magicNumber = GetOneMagicNumber(100);
	_log.info("Dll Static ({0:03d} - {1})", magicNumber, title);
	return;
}

CDllStatic::~CDllStatic()
{
	_log.info("Dll Static ({0:03d} - delete)", magicNumber);
	return;
}

void CDllStatic::PrintOut(const char* msg)
{
	_log.info("Dll Static PrintOut ({0:03d} - {1})", magicNumber, msg);
}