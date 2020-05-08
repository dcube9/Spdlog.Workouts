// LogWithDlls.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <windows.h>
#include <string>

#include "spdlog/spdlog.h"

#include "spdlog/sinks/basic_file_sink.h"		// support for basic file logging
#include "spdlog/sinks/daily_file_sink.h"		// support for daily-basic file logging
#include "spdlog/sinks/rotating_file_sink.h"	// support for rotating file logging
//
#include "spdlog/sinks/stdout_color_sinks.h"	// or "../stdout_sinks.h" if no colors needed
#include "spdlog/sinks/stdout_sinks.h"

#include "..\DllStatic\DllStatic.h"
#include "..\DllDynamic\DllDynamic.h"
#include "..\SingletonLog\SingletonLog.h"

#include "DynamicModule.h"
#include "Utilities.h"

using namespace std;



shared_ptr<CDllStatic> objStatic4(new CDllStatic("Call from : MAIN - Heap in global"));
CDllStatic objStatic3("Call from : MAIN - Stack in global");



//
//static spdlog::logger ILOG()
//{
//	//static auto logger = spdlog::basic_logger_mt("basic_logger", IA_Log_FilePath("basic_logger_mt.txt").string());
//	static std::vector<spdlog::sink_ptr> mySinks = ILOG_GetSinks();
//	static auto	logger = std::make_shared<spdlog::logger>("", std::begin(mySinks), std::end(mySinks));
//
//	spdlog::set_default_logger(logger);
//	
//	return *(logger.get());
//}

//static std::vector<spdlog::sink_ptr> ILOG_GetSinks()
//{
//	std::vector<spdlog::sink_ptr> sinks;
//	sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
//	sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_mt>(IA_Log_FilePath("logfile"), 23, 59));
//
//	return sinks;
//}
//
//extern "C"
//{
//
//
//	__declspec(dllexport) spdlog::logger* GetLogger()
//	{
//		//static std::vector<spdlog::sink_ptr> mySinks = ILOG_GetSinks();
//		//static spdlog::logger* logger = new spdlog::logger("", std::begin(mySinks), std::end(mySinks));
//		static auto logger = spdlog::basic_logger_st("basic_logger", IA_Log_FilePath("basic_logger_mt.txt"));
//
//		return logger.get();
//	}
//}

int main()
{
	_log.info("*** Main() - First line");

	//ILOG();

	//spdlog::info("Welcome to spdlog version {}.{}.{}  !", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);
	//ILOG().info("Welcome to spdlog version {}.{}.{}  !", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);

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

