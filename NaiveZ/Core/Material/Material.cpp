#include <utility>
using namespace std;

#include "Include/Material.h"
//#include "SOIL/SOIL/soil.h"

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
	if (category == "map_Kd")
	{
		map_Kd_ = name;
		KdTexPtr_ = unique_ptr<Texture>(new Texture(name));
	}
	else if (category == "map_Bump")
	{
		map_Bump_ = name;
		BumpTexPtr_ = unique_ptr<Texture>(new Texture(name));
	}
	else if (category == "map_Ke")
	{
		map_Ke_ = name;
		KeTexPtr_ = unique_ptr<Texture>(new Texture(name));
	}
	else if (category == "map_Ks")
	{
		map_Ks_ = name;
		KsTexPtr_ = unique_ptr<Texture>(new Texture(name));
	}
}
