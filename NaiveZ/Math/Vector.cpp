#include <math.h>

#include "Include\Vector.h"
#include "Include\Utils.h"


namespace NaiveZ3D
{
	//******************  Vector2 **********************
	Vector2::Vector2(const Vector2& v)
	{
		x_ = v.x_;
		y_ = v.y_;
	}
	Vector2& Vector2::operator = (const Vector2& v)
	{
		x_ = v.x_;
		y_ = v.y_;
		return *this;
	}

	//******************  Vector3 **********************
	Vector3::Vector3(const Vector3& v)
	{
		x_ = v.x_;
		y_ = v.y_;
		z_ = v.z_;
	}

	Vector3& Vector3::operator = (const Vector3& v)
	{
		x_ = v.x_;
		y_ = v.y_;
		z_ = v.z_;
		return *this;
	}

	float Vector3::length()const
	{
		auto len = x_ * x_ + y_ * y_ + z_ * z_;
		return sqrtf(len);
	}

	void Vector3::normalize()
	{
		auto len = length();
		auto reciprocal = 1.0f / len;

		x_ *= reciprocal;
		y_ *= reciprocal;
		z_ *= reciprocal;
	}

	float Vector3::dotProduct(const Vector3& v)const
	{
		return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
	}

	Vector3 Vector3::crossProduct(const Vector3& v)const
	{
		return Vector3(y_ * v.z_ - z_ * v.y_, z_ * v.x_ - x_ * v.z_, x_ * v.y_ - y_ * v.x_);
	}

	//v' = (this) * (1 - t) + v * t
	Vector3 Vector3::lerp(const Vector3& v, float t)
	{
		return Vector3(x_ * (1 - t) + t * v.x_,
			y_ * (1 - t) + t * v.y_,
			z_ * (1 - t) + t * v.z_);
	}

	bool operator == (const Vector3& v1, const Vector3& v2)
	{
		return FloatEqual(v1.x_, v2.x_) && FloatEqual(v1.y_, v2.y_) && FloatEqual(v1.z_, v2.z_);
	}
	bool operator != (const Vector3& v1, const Vector3& v2)
	{
		return !(v1 == v2);
	}
	Vector3 operator + (const Vector3& v1, const Vector3& v2)
	{
		return Vector3(v1.x_ + v2.x_, v1.y_ + v2.y_, v1.z_ + v2.z_);
	}
	Vector3 operator - (const Vector3& v1, const Vector3& v2)
	{
		return Vector3(v1.x_ - v2.x_, v1.y_ - v2.y_, v1.z_ - v2.z_);
	}
	Vector3 operator * (float k, const Vector3& v)
	{
		return Vector3(k * v.x_, k * v.y_, k * v.z_);
	}

	//******************  Vector4 **********************
	Vector4::Vector4(const Vector4& v)
	{
		x_ = v.x_;
		y_ = v.y_;
		z_ = v.z_;
		w_ = v.w_;
	}

	Vector4::Vector4(const Vector3& v, float w)
	{
		x_ = v.x_;
		y_ = v.y_;
		z_ = v.z_;
		w_ = w;
	}

	Vector4& Vector4::operator = (const Vector4& v)
	{
		x_ = v.x_;
		y_ = v.y_;
		z_ = v.z_;
		w_ = v.w_;

		return *this;
	}

	void Vector4::normalize()
	{
		auto len = length();

		x_ /= len;
		y_ /= len;
		z_ /= len;
		w_ /= len;
	}

	float Vector4::length()const
	{
		return sqrtf(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);;
	}

	void Vector4::homogeneous()
	{
		x_ /= w_;
		y_ /= w_;
		z_ /= w_;
		w_ /= w_;
	}
}