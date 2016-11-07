#include "Include\MaterialMgr.h"

NaiveZ3D::MaterialMgr & NaiveZ3D::MaterialMgr::Instance()
{
	static MaterialMgr self;
	if (!self.mInited_)
	{
		self.Init();
	}
	return self;
}

void NaiveZ3D::MaterialMgr::Init()
{
}

void NaiveZ3D::MaterialMgr::LoadMtl(const std::string & mtlName)
{
}

NaiveZ3D::Material & NaiveZ3D::MaterialMgr::GetMaterial(const std::string & mtl)
{
	return mMaterialCache_[mtl];
}
