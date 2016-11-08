#include <utility>
using namespace std;

#include "Include\Material.h"

NaiveZ3D::Material::Material(const std::string & name)
	:mName_(name)
{
}

void NaiveZ3D::Material::AddMtlData(MtlData && data)
{
	mMtlDataMap_[data.newmtl_] = move(data);
}

void NaiveZ3D::MtlData::ReadTexture(const std::string & name, const std::string & category)
{
}
