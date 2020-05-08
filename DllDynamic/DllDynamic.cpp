// DllDynamic.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include <stdio.h>
#include <cstdlib>
#include <memory>

#include "DllDynamic.h"

#include "..\SingletonLog\SingletonLog.h"
#include "..\DllStatic\DllStatic.h"

using namespace std;

CDllStatic objStatic1("Call from : Dll Static - Stack in global");
shared_ptr<CDllStatic> objStatic2(new CDllStatic("Call from : Dll Static - Heap in global"));

unsigned int GetOneMagicNumber(unsigned int max) // from 1 to max
{
	unsigned int x = max + 1;

	while (x > max)
		x = 1 + std::rand() / ((RAND_MAX + 1u) / max);  // Note: 1+rand()%6 is biased

	return x;
}

class CDllDynamic : public IDllDynamic
{
public:
	CDllDynamic(const char* title)
	{
		magicNumber = GetOneMagicNumber(100);
		_log.info("Dll Dynamic ({0:03d} - {1})", magicNumber, title);
		return;
	}

	virtual ~CDllDynamic()
	{
		_log.info("Dll Dynamic ({0:03d} - delete)", magicNumber);
		return;
	}

	virtual void PrintOut(const char* msg) override
	{
		_log.info("Dll Dynamic PrintOut ({0:03d} - {1})", magicNumber, msg);
	}

private:
	unsigned int magicNumber;
};


CDllDynamic objDynamic1("Call from : Dll Dynamic - Stack in global");
shared_ptr<CDllDynamic> objDynamic2(new CDllDynamic("Call from : Dll Dynamic - Heap in global"));


// This is an example of an exported function.
extern "C" 
{
	DLLDYNAMIC_API IDllDynamic* FactoryDllDynamic(const char* title)
	{
		return new CDllDynamic(title);
	}
}
