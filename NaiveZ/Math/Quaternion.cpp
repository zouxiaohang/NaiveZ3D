#include "Include\Quaternion.h"

#include <math.h>

namespace NaiveZ3D
{
	Quaternion::Quaternion(const Quaternion& q)
	{
		w_ = q.w_;
		v_ = q.w_;
	}

	Quaternion& Quaternion::operator = (const Quaternion& q)
	{
		w_ = q.w_;
		v_ = q.v_;
		return *this;
	}

	Quaternion Quaternion::crossPrduct(const Quaternion& q)const
	{
		return Quaternion(w_ * q.w_ - v_.dotProduct(q.v_),
			w_ * q.v_ + q.w_ * v_ + q.v_.crossProduct(v_));
	}

	Quaternion Quaternion::slerp(const Quaternion& q, float t)const
	{
		auto cosOmega = w_ * q.w_ + v_.dotProduct(q.v_);
		auto tempQ = q;
		if (cosOmega < 0.0f)
		{
			tempQ.w_ = tempQ.w_;
			tempQ.v_ = -tempQ.v_;
			cosOmega = -cosOmega;
		}
		float k0, k1;
		if (cosOmega > 0.9999f)
		{
			k0 = 1.0f - t;
			k1 = t;
		}
		else
		{
			auto sinOmega = sqrtf(1.0f - cosOmega * cosOmega);
			auto omega = atan2f(sinOmega, cosOmega);
			k0 = sinf((1.0f - t) * omega) / sinOmega;
			k1 = sinf(t * omega) / sinOmega;
		}

		return Quaternion(w_ * k0 + q.w_ * k1,
			Vector3(v_.x_ * k0 + q.v_.x_ * k1,
				v_.y_ * k0 + q.v_.y_ * k1,
				v_.z_ * k0 + q.v_.z_ * k1));
	}
}