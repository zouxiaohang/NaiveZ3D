#pragma once

namespace NaiveZ3D
{
	class Vector3
	{
	public:
		Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) :x_(x), y_(y), z_(z) {}
		Vector3(const Vector3& v);
		Vector3& operator = (const Vector3& v);

		void normalize();
		float length()const;

		float dotProduct(const Vector3& v)const;
		Vector3 crossProduct(const Vector3& v)const;

		Vector3 lerp(const Vector3& v, float t);

		Vector3 operator - ()const { return Vector3(-x_, -y_, -z_); }
	public:
		float x_;
		float y_;
		float z_;
	};

	bool operator == (const Vector3& v1, const Vector3& v2);
	bool operator != (const Vector3& v1, const Vector3& v2);
	Vector3 operator + (const Vector3& v1, const Vector3& v2);
	Vector3 operator - (const Vector3& v1, const Vector3& v2);
	Vector3 operator * (float k, const Vector3& v);

	class Vector4
	{
	public:
		Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) :x_(x), y_(y), z_(z), w_(w) {}
		Vector4(const Vector3& v, float w);
		Vector4(const Vector4& v);
		Vector4& operator = (const Vector4& v);

		void normalize();
		float length()const;
		void homogeneous();

		Vector4 operator - ()const { return Vector4(-x_, -y_, -z_, w_); }
	public:
		float x_;
		float y_;
		float z_;
		float w_;
	};
}