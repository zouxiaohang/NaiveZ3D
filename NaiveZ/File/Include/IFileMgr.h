#pragma once

#include <string>

#include "Model.h"

namespace NaiveZ3D
{
	class IFileMgr
	{
	public:
		IFileMgr(){}
		virtual ~IFileMgr() {}

		virtual Model Load(const std::string& fileName) = 0;

	private:
		
	};
}