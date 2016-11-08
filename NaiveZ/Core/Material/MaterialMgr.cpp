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
