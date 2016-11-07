#pragma once

#include <string>
#include <vector>

#include "../../Utils/Include/Constant.h"

namespace NaiveZ3D
{
	struct Face
	{
		Face(const std::vector<std::vector<std::string>>& face)
		{
			for (auto i = 0; i != face.size(); ++i)
			{
				// 注意！索引从0开始！！！
				if (face[i][0] != "")
					mVertexIndex_.push_back(stoul(face[i][0])-1);
				if (face[i].size() >= 2 && face[i][1] != "")
					mTextureIndex_.push_back(stoul(face[i][1])-1);
				if (face[i].size() >= 3 && face[i][2] != "")
					mNormalIndex_.push_back(stoul(face[i][2])-1);
			}
		}

		std::vector<UINT32> mVertexIndex_;
		std::vector<UINT32> mTextureIndex_;
		std::vector<UINT32> mNormalIndex_;
	};
}