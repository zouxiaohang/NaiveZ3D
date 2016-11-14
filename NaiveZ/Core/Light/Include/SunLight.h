#pragma once

#include <memory>

#include "../../../Math/Include/Vector.h"

namespace NaiveZ3D
{
	class SunLight
	{
	public:
		SunLight(Vector3 d, Vector3 c = Vector3(1,1,1))
			:mDir_(d),
			mColor_(c)
		{}

		void SetColor(Vector3 c);
		Vector3 GetColor()const;

		void SetDir(Vector3 d);
		Vector3 GetDir()const;

	private:
		Vector3 mDir_;
		Vector3 mColor_;
	};

	using SunLightPtr = std::unique_ptr<SunLight>;
}