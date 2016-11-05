#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include "Include\IOBJFileMgr.h"
#include "../Math/Include/Vector.h"
#include "../Utils/Include/Constant.h"
#include "../Utils/Include/Helper.h"
#include "Include\Model.h"
#include "Include\Face.h"

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
		string buf;
		string tok;
		while (getline(ifs, buf))
		{
			stringstream line(buf);
			line >> tok;
			if (tok == "#")
				continue;

			if (tok == "mtllib")
			{
				string mtl;
				line >> mtl;
				model.setMtl(mtl);
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
					mesh.SetVertexBuffer(vBuffer);
					mesh.SetTextureCoordBuffer(tcBuffer);
					mesh.SetNormalBuffer(nBuffer);
					mesh.SetFaceBuffer(fBuffer);
					model.AddMesh(mesh);
					vBuffer.clear();
					tcBuffer.clear();
					nBuffer.clear();
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
				while (line >> msg)
				{
					auto res = Helper::Split(msg, "/");
					auto face = Face(stoul(res[0]), stoul(res[1]), stoul(res[2]));
					fBuffer.push_back(face);
				}
			}
		}

		if (!vBuffer.empty())
		{
			mesh.SetName(meshName);
			mesh.SetVertexBuffer(vBuffer);
			mesh.SetTextureCoordBuffer(tcBuffer);
			mesh.SetNormalBuffer(nBuffer);
			mesh.SetFaceBuffer(fBuffer);
			model.AddMesh(mesh);
		}

		return model;
	}
}