#pragma once

#include <memory>

#include "../../../Math/Include/Vector.h"

namespace NaiveZ3D
{
	class PointLight
	{
	public:
		PointLight(Vector3 p, Vector3 c = Vector3(1,1,1), float r = 10.0f, float ca = 1.0f, float la = 0.0f, float qa = 0.0f)
			:mPosition_(p),
			mColor_(c),
			mRange_(r),
			mConstAtten_(ca),
			mLinearAtten_(la),
			mQuadAtten_(qa)
		{}
		PointLight(const PointLight&);

	private:
		Vector3 mPosition_;
		Vector3 mColor_;
		float mRange_;
		float mConstAtten_;
		float mLinearAtten_;
		float mQuadAtten_;
	};

	using PointLightPtr = std::unique_ptr<PointLight>;
}