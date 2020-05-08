#pragma once
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DLLDYNAMIC_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DLLDYNAMIC_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef DLLDYNAMIC_EXPORTS
#define DLLDYNAMIC_API __declspec(dllexport)
#else
#define DLLDYNAMIC_API __declspec(dllimport)
#endif

// This class is exported from the DllDynamic.dll
class DLLDYNAMIC_API IDllDynamic 
{
public:
	virtual ~IDllDynamic() = default;

	virtual void PrintOut(const char* msg) = 0;
};


typedef IDllDynamic* (*FactoryDllDynamic_f)(const char* title);


extern "C"
{
	DLLDYNAMIC_API IDllDynamic* FactoryDllDynamic(const char* title);
}
