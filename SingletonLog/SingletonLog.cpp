+// SingletonLog.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <stdexcept>
#include <memory>
#include <string>
#include <filesystem>
#include "SingletonLog.h"

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

#include "spdlog/sinks/basic_file_sink.h"		// support for basic file logging
#include "spdlog/sinks/daily_file_sink.h"		// support for daily-basic file logging
#include "spdlog/sinks/rotating_file_sink.h"	// support for rotating file logging
//
#include "spdlog/sinks/stdout_color_sinks.h"	// or "../stdout_sinks.h" if no colors needed
#include "spdlog/sinks/stdout_sinks.h"

static std::shared_ptr<spdlog::logger> GetLogger()
{
	std::shared_ptr<spdlog::logger> logger = nullptr;

	/*
	*	CONFIG HERE EVERYTHING YOU WANT ABOUT YOUR LOG
	*
	*   e.g.:  Load from config files, read from registry ....
	*/

	int logMode = 1;

	switch (logMode)
	{
	case 0:
		logger = spdlog::basic_logger_mt("basic_logger", IA_Log_FilePath("basic_logger_mt.log"));
		break;

	case 1:
		{
			std::vector<spdlog::sink_ptr> mySinks;
			mySinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
			mySinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_mt>(IA_Log_FilePath("logfile.log"), 23, 59));
			logger.reset(new spdlog::logger("", std::begin(mySinks), std::end(mySinks)));
		}
		break;

	default:
		logger = spdlog::default_logger();
		break;
	}

	return logger;
}

static std::shared_ptr<spdlog::logger> GetAndInitLogger()
{
	std::shared_ptr<spdlog::logger> mainLog = GetLogger();

	mainLog->info("Welcome to spdlog version {}.{}.{}  !", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);

	return mainLog;
}

SINGLETONLOG_API spdlog::logger& GetIstanceLog()
{
	static std::shared_ptr<spdlog::logger>logInstance = nullptr;

	if (logInstance == nullptr)
	{
		logInstance = GetAndInitLogger();

		if (logInstance == nullptr)
			throw new std::logic_error("Cant create spdlog object !");
	}

	return *logInstance;
}