#include <string>
#include <iostream>
using namespace std;

#include "LoggerMgrUniTest.h"
#include "../Logger/Include/LoggerMgr.h"

bool NaiveZ3D::UniTest::LoggerMgrUniTest::Test()
{
	LoggerMgr::Instance().Debug("Debug Test1.........");
	LoggerMgr::Instance().Info("Info Test1...........");
	LoggerMgr::Instance().Error("Error Test1..........");

	LoggerMgr::Instance().SetLogLevel(LoggerMgr::Level::Info);
	LoggerMgr::Instance().Debug("Debug Test2.........");
	LoggerMgr::Instance().Info("Info Test2.........");
	LoggerMgr::Instance().Error("Error Test2.........");

	LoggerMgr::Instance().SetLogLevel(LoggerMgr::Level::Error);
	LoggerMgr::Instance().Debug("Debug Test3.........");
	LoggerMgr::Instance().Info("Info Test3............");
	LoggerMgr::Instance().Error("Error Test3..........");

	SetConsoleColor(ConsoleColor::GREEN);
	cout << "LoggerMgrUniTest UniTest Pass" << endl;
	SetConsoleColor();

	return true;
}
