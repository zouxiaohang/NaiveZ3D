#pragma once

#include "../../Utils/Include/Constant.h"

namespace NaiveZ3D
{
	struct Face
	{
		Face(UINT32 v, UINT32 t, UINT32 n)
			:mVertexIndex_(v),
			mTextureIndex_(t),
			mNormalIndex_(n)
		{}

		UINT32 mVertexIndex_;
		UINT32 mTextureIndex_;
		UINT32 mNormalIndex_;
	};
}