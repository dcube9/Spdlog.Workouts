#pragma once
#include <string>
#include <filesystem>
namespace fs = std::experimental::filesystem;

fs::path App_Path(void);
std::string Log_FilePath(const char* filename);