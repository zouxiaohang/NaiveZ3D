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
		//Vector3 PareseVertex(const std::stringstream& v);
		//Vector3 ParseNormal(const std::stringstream& n);
		//Face ParseFace(const std::string& f);
	};
}