#pragma once

#include "../../Math/Include/Vector.h"
#include "../../Math/Include/Matrix.h"
#include "glm/glm_include.h"

namespace NaiveZ3D
{
	class Camera
	{
	public:
		Camera(){}
		Camera(Vector3 pos, Vector3 target, Vector3 up, Vector3 right);

		void Translate(Vector3 trans);
		//void Rotate()

		Matrix GetViewTransfrom()const { return mViewTransfrom_; }
	private:
		void BuildViewTransform();
	private:
		Vector3 mPos_;
		Vector3 mTarget_;
		Vector3 mUp_;
		Vector3 mRight_;
		Matrix mViewTransfrom_;
	};
}