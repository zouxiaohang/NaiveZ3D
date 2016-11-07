#pragma once

#include "../../Math/Include/Vector.h"
#include "glm/glm_include.h"

namespace NaiveZ3D
{
	class Camera
	{
	public:
		Camera(Vector3 pos, Vector3 target, Vector3 up, Vector3 right);


	private:
		Vector3 mPos_;
		Vector3 mTarget_;
		Vector3 mUp_;
		Vector3 mRight_;
	};
}