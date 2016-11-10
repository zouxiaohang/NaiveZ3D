#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include "Include/IOBJFileMgr.h"
#include "../Math/Include/Vector.h"
#include "../Utils/Include/Constant.h"
#include "../Utils/Include/Helper.h"
#include "Include/Model.h"
#include "Include/Face.h"
#include "../Core/Material/Include/MaterialMgr.h"
#include "../UniTest/UniTest.h"

using namespace std;

namespace NaiveZ3D
{
	Model IOBJFileMgr::Load(const std::string& name)
	{
		Model model;
		Mesh mesh;
		string meshName;
		vector<Vector3> vBuffer;
		vector<Normal> nBuffer;
		vector<TextureCoord> tcBuffer;
		vector<Face> fBuffer;
		string useMtl;

		ifstream ifs(name);
		if (!ifs)
		{
			UniTest::UniTest::SetConsoleColor(UniTest::UniTest::ConsoleColor::RED);
			cout << "Fail to open OBJ file->" + name << endl;
			UniTest::UniTest::SetConsoleColor();
			return model;
		}
		model.SetModelName(name);
		string buf;
		
		while (getline(ifs, buf))
		{
			string tok;
			stringstream line(buf);
			line >> tok;
			if (tok == "#")
				continue;

			if (tok == "mtllib")
			{
				string mtl;
				line >> mtl;
				auto path = name.substr(0, name.rfind('/')+1);
				mtl = path + mtl;
				model.SetMtl(mtl);
				LoadMtl(mtl);
			}
			else if (tok == "usemtl")
			{
				line >> useMtl;
			}
			else if (tok == "o")
			{
				if (meshName != "")
				{
					mesh.SetName(meshName);
					mesh.SetMtl(useMtl);
					//mesh.SetVertexBuffer(vBuffer);
					//mesh.SetTextureCoordBuffer(tcBuffer);
					//mesh.SetNormalBuffer(nBuffer);
					mesh.SetFaceBuffer(fBuffer);
					model.AddMesh(mesh);
					//vBuffer.clear();
					//tcBuffer.clear();
					//nBuffer.clear();
					fBuffer.clear();
				}
				line >> meshName;
			}
			else if (tok == "v")
			{
				float x, y, z;
				line >> x >> y >> z;
				auto v = Vector3(x, y, z);
				vBuffer.push_back(v);
			}
			else if (tok == "vt")
			{
				float x, y;
				line >> x >> y;
				auto tc = TextureCoord(x, y);
				tcBuffer.push_back(tc);
			}
			else if (tok == "vn")
			{
				float x, y, z;
				line >> x >> y >> z;
				auto n = Normal(x, y, z);
				nBuffer.push_back(n);
			}
			else if (tok == "f")
			{
				string msg;
				vector<vector<string>> f;
				while (line >> msg)
				{
					auto res = Helper::Split(msg, "/");
					f.push_back(res);
				}
				auto face = Face(f);
				fBuffer.push_back(face);
			}
		}

		if (!vBuffer.empty())
		{
			mesh.SetName(meshName);
			mesh.SetMtl(useMtl);
			//mesh.SetVertexBuffer(vBuffer);
			//mesh.SetTextureCoordBuffer(tcBuffer);
			//mesh.SetNormalBuffer(nBuffer);
			mesh.SetFaceBuffer(fBuffer);
			model.AddMesh(mesh);
			model.SetVertexBuffer(move(vBuffer));
			model.SetTextureCoordBuffer(move(tcBuffer));
			model.SetNormalBuffer(move(nBuffer));
		}

		return model;
	}
	void IOBJFileMgr::LoadMtl(const std::string & mtlName)
	{
		MaterialMgr::Instance().LoadMtl(mtlName);
	}
}