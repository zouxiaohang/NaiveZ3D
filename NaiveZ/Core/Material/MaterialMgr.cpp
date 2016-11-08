#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

#include "Include/MaterialMgr.h"
#include "../../UniTest/UniTest.h"

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
		UniTest::UniTest::SetConsoleColor(UniTest::UniTest::ConsoleColor::RED);
		cout << "Fail to open OBJ file->" + mtlName << endl;;
		UniTest::UniTest::SetConsoleColor();
		return;
	}
	string line;
	string tok;
	MtlData mtlData;
	Material material(mtlName);

	while (getline(ifs, line))
	{
		stringstream ss(line);
		ss >> tok;
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
