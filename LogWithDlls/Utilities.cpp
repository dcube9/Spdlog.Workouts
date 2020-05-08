#include "stdafx.h"
#include <string>
#include <filesystem>

#define WIN32_LEAN_AND_MEAN      // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <libloaderapi.h>

#include "Utilities.h"

using namespace std;
namespace fs = std::experimental::filesystem;

fs::path IA_App_Path(void)
{
	fs::path ret = ".\\";
	char exePath[2048];

	if ((GetModuleFileName(NULL, exePath, 2048) != 0))
	{
		ret = exePath;
		ret = ret.remove_filename();
	}

	return ret;
}

std::string IA_Log_FilePath(const char* filename)
{
	return IA_App_Path().append("logs").append(filename).string();
}
