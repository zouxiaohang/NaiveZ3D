#pragma once

#include <string>
#include <vector>
#include <cassert>
#include "../../Logger/Include/LoggerMgr.h"

namespace NaiveZ3D
{
namespace Helper
{
	std::vector<std::string> Split(const std::string& msg, const std::string& delimiter = " ");

#define ZAssert(f, info)\
do{\
	bool __ret = f;\
	if(!__ret)\
	{\
		NaiveZ3D::LoggerMgr::Instance().Error(info);\
		assert(false);\
	}\
}while(0)



}
}