#include <fstream>
#include <sstream>

using namespace std;

#include "Include/MaterialMgr.h"
#include "../../UniTest/UniTest.h"
#include "SOIL/SOIL/soil.h"
#include "../../Logger/Include/LoggerMgr.h"

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
	ifstream ifs(mtlName);
	if (!ifs)
	{
		LoggerMgr::Instance().Error("Fail to open OBJ file->" + mtlName);
		return;
	}
	string line;
	MtlData mtlData;
	Material material(mtlName);
	string path = mtlName.substr(0, mtlName.rfind('/') + 1);

	while (getline(ifs, line))
	{
		stringstream ss(line);
		string tok;
		ss >> tok;
		if (tok == "#")
			continue;
		if (tok == "newmtl")
		{
			if (mtlData.newmtl_ != "")
				material.AddMtlData(move(mtlData));
			mtlData.Clear();
			ss >> mtlData.newmtl_;
		}
		else if (tok == "Ns")
		{
			float Ns;
			ss >> Ns;
			mtlData.Ns_ = Ns;
			mtlData.useNs_ = true;
		}
		else if (tok == "Ka")
		{
			float x, y, z;
			ss >> x >> y >> z;
			mtlData.Ka_ = Vector3(x, y, z);
			mtlData.useKa_ = true;
		}
		else if (tok == "Kd")
		{
			float x, y, z;
			ss >> x >> y >> z;
			mtlData.Kd_ = Vector3(x, y, z);
			mtlData.useKd_ = true;
		}
		else if (tok == "Ks")
		{
			float x, y, z;
			ss >> x >> y >> z;
			mtlData.Ks_ = Vector3(x, y, z);
			mtlData.useKs_ = true;
		}
		else if (tok == "Ke")
		{
			float x, y, z;
			ss >> x >> y >> z;
			mtlData.Ke_ = Vector3(x, y, z);
			mtlData.useKe_ = true;
		}
		else if (tok == "Ni")
		{
			float Ni;
			ss >> Ni;
			mtlData.Ni_ = Ni;
			mtlData.useNi_ = true;
		}
		else if (tok == "d")
		{
			float d;
			ss >> d;
			mtlData.d_ = d;
			mtlData.used_ = true;
		}
		else if (tok == "illum")
		{
			int illum;
			ss >> illum;
			mtlData.illum_ = illum;
			mtlData.useillum_ = true;
		}
		else if (tok == "map_Kd" || tok == "map_Bump" || tok == "map_Ke" || tok == "map_Ks")
		{
			string tex;
			ss >> tex;
			if (tex == "")continue;
			tex = path +tex;
			mtlData.ReadTexture(tex, tok);
		}
		else if (tok == "refl")
		{
			//ÔÝÊ±²»½âÎö
		}
	}
	if (mtlData.newmtl_ != "")
		material.AddMtlData(move(mtlData));

	AddMaterial(move(material));
}

NaiveZ3D::Material & NaiveZ3D::MaterialMgr::GetMaterial(const std::string & mtl)
{
	return mMaterialCache_[mtl];
}

void NaiveZ3D::MaterialMgr::AddMaterial(Material && material)
{
	mMaterialCache_[material.GetName()] = move(material);
}

bool NaiveZ3D::MaterialMgr::HasImageData(const std::string &name) const
{
	return mImageDataCache_.find(name) != mImageDataCache_.end();
}

const std::tuple<unsigned char*, GLint, GLint>& NaiveZ3D::MaterialMgr::GetImageData(const std::string &name) const
{
	return mImageDataCache_.find(name)->second;
}

void NaiveZ3D::MaterialMgr::AddImageData(const std::string &name, unsigned char *image, GLint w, GLint h)
{
	mImageDataCache_[name] = make_tuple(image, w, h);
}

void NaiveZ3D::MaterialMgr::ClearImageDataCache()
{
	for (const auto& item : mImageDataCache_)
	{
		SOIL_free_image_data(get<0>(item.second));
	}
}
