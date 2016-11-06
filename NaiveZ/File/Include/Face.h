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
				mVertexIndex_.push_back(stoul(face[i][0]));
				mTextureIndex_.push_back(stoul(face[i][1]));
				mNormalIndex_.push_back(stoul(face[i][2]));
			}
		}

		std::vector<UINT32> mVertexIndex_;
		std::vector<UINT32> mTextureIndex_;
		std::vector<UINT32> mNormalIndex_;
	};
}