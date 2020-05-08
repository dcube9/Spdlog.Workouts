#pragma once
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DLLSTATIC_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DLLSTATIC_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef DLLSTATIC_EXPORTS
#define DLLSTATIC_API __declspec(dllexport)
#else
#define DLLSTATIC_API __declspec(dllimport)
#endif

// This class is exported from the DllStatic.dll
class DLLSTATIC_API CDllStatic {
public:
	CDllStatic(const char* title);
	~CDllStatic();

	void PrintOut(const char* msg);

private:
	int magicNumber;
};
