#pragma once

#include "IFileMgr.h"

namespace NaiveZ3D
{
	class IOBJFileMgr : IFileMgr
	{
	public:
		IOBJFileMgr()
			:IFileMgr()
		{

		}

		virtual ~IOBJFileMgr(){}

		virtual Model Load(const std::string& name);
	};
}