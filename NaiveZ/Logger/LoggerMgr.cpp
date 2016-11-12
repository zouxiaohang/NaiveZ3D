#include "Include/LoggerMgr.h"

#include <cassert>
#include <ctime>
#ifdef OutputToConsole
#include <iostream>
#endif
using namespace std;

#include <Windows.h>

NaiveZ3D::LoggerMgr & NaiveZ3D::LoggerMgr::Instance()
{
	static LoggerMgr self;
	if (!self.mInited_)
	{
		self.Init();
	}
	return self;
}

void NaiveZ3D::LoggerMgr::SetLogLevel(Level l)
{
	mLogLevel_ = l;
}

void NaiveZ3D::LoggerMgr::Debug(const std::string &debug)
{
	if (mLogLevel_ <= Level::Debug)
	{
		*mFilePtr_ << GetTime() << "[Debug] -> " << debug << endl;
#ifdef OutputToConsole
		cout << "[Debug] -> " << debug << endl;
#endif
	}
}

void NaiveZ3D::LoggerMgr::Info(const std::string &info)
{
	if (mLogLevel_ <= Level::Info)
	{
		*mFilePtr_ << GetTime() << "[Info] -> " << info << endl;
#ifdef OutputToConsole
		cout << "[Info] -> " << info << endl;
#endif
	}
}

void NaiveZ3D::LoggerMgr::Error(const std::string &error)
{
	if (mLogLevel_ <= Level::Error)
	{
		*mFilePtr_ << GetTime() << "[Error] -> " << error << endl;
#ifdef OutputToConsole
		SetConsoleColor(ConsoleColor::RED);
		cout << "[Error] -> " << error << endl;
		SetConsoleColor();
#endif
	}
}

void NaiveZ3D::LoggerMgr::SetConsoleColor(ConsoleColor c)
{
	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);
	int color;
	if (c == ConsoleColor::WHITE)
		color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
	else if (c == ConsoleColor::RED)
		color = FOREGROUND_RED;
	else if (c == ConsoleColor::GREEN)
		color = FOREGROUND_GREEN;
	SetConsoleTextAttribute(hdl, color | FOREGROUND_INTENSITY);
}

void NaiveZ3D::LoggerMgr::Init()
{
	mFilePtr_ = FilePtr(new ofstream("./gamelog.log", ios_base::out | ios_base::trunc));
	assert(mFilePtr_ && mFilePtr_->is_open());
	mInited_ = true;
}

std::string NaiveZ3D::LoggerMgr::GetTime() const
{
	auto t = time(NULL);
	auto lt = localtime(&t);
	char *format = "%02d:%02d:%02d";
	string buf(8, '\0');
	sprintf(&buf[0], format, lt->tm_hour, lt->tm_min, lt->tm_sec);
	return "["+buf+"]";
}
