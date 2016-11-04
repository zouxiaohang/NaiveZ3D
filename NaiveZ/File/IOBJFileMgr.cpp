#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include "Include\IOBJFileMgr.h"
#include "../Math/Include/Vector.h"
#include "../Utils/Include/Constant.h"
#include "Include\Model.h"

using namespace std;

namespace NaiveZ3D
{
	Model IOBJFileMgr::Load(const std::string& name)
	{
		Model model;
		vector<Vector3> vBuffer;
		vector<UINT32> iBuffer;

		ifstream ifs(name);
		string buf;
		string tok;
		while (getline(ifs, buf))
		{
			stringstream line(buf);
			while (line >> tok)
			{
				if (tok == "v")
				{
				}
				else if (tok == "vn")
				{

				}
				else if (tok == "f")
				{

				}
			}
			cout << endl;
		}

		return model;
	}
}