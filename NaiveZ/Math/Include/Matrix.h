#pragma once

namespace NaiveZ3D
{
	class Vector3;
	class Vector4;
	class Quaternion;

	class Matrix
	{
	public:
		Matrix();
		Matrix(float mat[16]);
		Matrix(const Matrix& mat);
		Matrix& operator = (const Matrix& mat);

		void Identity();
		float Determinant()const;
		void Inverse();

		void SetScale(const Vector3& s);
		void SetRotationX(float angle);
		void SetRotationY(float angle);
		void SetRotationZ(float angle);
		void SetTranslation(const Vector3& t);

		void FromQuaternion(const Quaternion& q);
		Quaternion ToQuaternion()const;

		Vector4 ApplyVector4(const Vector4& v)const;

		void SetLookAtLH(const Vector3& eye, const Vector3& at, const Vector3& up);
		void SetPerspectiveLH(float w, float h, float zn, float zf);
		void SetPerspectiveFovLH(float fovy, float aspect, float zn, float zf);
	public:
		union
		{
			float mm_[4][4];
			struct
			{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
		};
	};

	Matrix operator *(float s, const Matrix& mat);
	Matrix operator *(const Matrix& m1, const Matrix& m2);
}