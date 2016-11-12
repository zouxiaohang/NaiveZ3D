#pragma once

#include <fstream>
#include <memory>
#include <string>

#define OutputToConsole

namespace NaiveZ3D
{
	
	class LoggerMgr
	{
	public:
		enum class Level
		{
			Debug = 0,
			Info,
			Error,
		};
	public:
		static LoggerMgr& Instance();

		void SetLogLevel(Level l);
		int GetLogLevel()const { return static_cast<int>(mLogLevel_); }

		void Debug(const std::string&);
		void Info(const std::string&);
		void Error(const std::string&);

	private:
		enum class ConsoleColor
		{
			WHITE,
			RED,
			GREEN,
		};
		void SetConsoleColor(ConsoleColor c = ConsoleColor::WHITE);

	private:
		LoggerMgr()
			:mInited_(false),
			mLogLevel_(Level::Debug)
		{}
		LoggerMgr(const LoggerMgr&);
		~LoggerMgr() { mFilePtr_->close(); }

		void Init();
		std::string GetTime()const;

	private:
		using FilePtr = std::unique_ptr<std::ofstream>;
		bool mInited_;

		Level mLogLevel_;
		FilePtr mFilePtr_;
	};
}