#pragma once
#include <string>
#include <filesystem>
namespace fs = std::experimental::filesystem;

fs::path IA_App_Path(void);
std::string IA_Log_FilePath(const char* filename);