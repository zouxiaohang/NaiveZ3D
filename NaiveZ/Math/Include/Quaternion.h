#pragma once

#include "Vector.h"

namespace NaiveZ3D
{
	class Quaternion
	{
	public:
		Quaternion(float w, const Vector3& v) :w_(w), v_(v) {}
		Quaternion(const Quaternion& q);
		Quaternion& operator = (const Quaternion& q);

		Quaternion crossPrduct(const Quaternion& q)const;

		Quaternion slerp(const Quaternion& q, float t)const;
	public:
		float w_;
		Vector3 v_;
	};
}
