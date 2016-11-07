#pragma once

#include <string>

#include "IFileMgr.h"

namespace NaiveZ3D
{
	class Vector3;

	class IOBJFileMgr : public IFileMgr
	{
	public:
		IOBJFileMgr()
			:IFileMgr()
		{

		}

		virtual ~IOBJFileMgr(){}

		virtual Model Load(const std::string& name);
		
	private:
		void LoadMtl(const std::string& mtlName);
	};
}