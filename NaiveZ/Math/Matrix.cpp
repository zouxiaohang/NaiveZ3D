#include "Include/Matrix.h"

#include "Include/Quaternion.h"
#include "Include/Vector.h"
#include "Include/Utils.h"

#include <cassert>
#include <math.h>
#include <string.h>

namespace NaiveZ3D
{
	Matrix::Matrix()
	{
		memset(mm_, 0, 16 * sizeof(float));
		_11 = _22 = _33 = _44 = 1.0f;
	}

	Matrix::Matrix(float mat[16])
	{
		_11 = mat[0]; _12 = mat[1]; _13 = mat[2]; _14 = mat[3];
		_21 = mat[4]; _22 = mat[5]; _23 = mat[6]; _24 = mat[7];
		_31 = mat[8]; _32 = mat[9]; _33 = mat[10]; _34 = mat[11];
		_41 = mat[12]; _42 = mat[13]; _43 = mat[14]; _44 = mat[15];
	}

	Matrix::Matrix(const Matrix& mat)
	{
		memcpy(mm_, mat.mm_, 16 * sizeof(float));
	}

	Matrix& Matrix::operator = (const Matrix& mat)
	{
		memcpy(mm_, mat.mm_, 16 * sizeof(float));
		return *this;
	}

	void Matrix::Identity()
	{
		memset(mm_, 0, 16 * sizeof(float));
		_11 = _22 = _33 = _44 = 1.0f;
	}

	float Matrix::Determinant()const
	{
		return _11 * (_22 * _33 - _23 * _32) +
			_12 * (_23 * _31 - _21 * _33) +
			_13 * (_21 * _32 - _22 * _31);
	}

	void Matrix::Inverse()
	{
		auto det = Determinant();
		assert(fabs(det) > 0.000001f);

		auto oneOverDet = 1.0f / det;
		auto r = *this;

		_11 = (r._22 * r._33 - r._23 * r._32) * oneOverDet;
		_12 = (r._13 * r._32 - r._12 * r._33) * oneOverDet;
		_13 = (r._12 * r._23 - r._13 * r._22) * oneOverDet;
		_14 = 0.0f;

		_21 = (r._23 * r._31 - r._21 * r._33) * oneOverDet;
		_22 = (r._11 * r._33 - r._13 * r._31) * oneOverDet;
		_23 = (r._13 * r._21 - r._11 * r._23) * oneOverDet;
		_24 = 0.0f;

		_31 = (r._21 * r._32 - r._22 * r._31) * oneOverDet;
		_32 = (r._12 * r._31 - r._11 * r._32) * oneOverDet;
		_33 = (r._11 * r._22 - r._12 * r._21) * oneOverDet;
		_34 = 0.0f;

		_41 = -(r._41 * _11 + r._42 * _21 + r._43 * _31);
		_42 = -(r._41 * _12 + r._42 * _22 + r._43 * _32);
		_43 = -(r._41 * _13 + r._42 * _23 + r._43 * _33);
		_44 = 1.0f;
	}

	void Matrix::SetScale(const Vector3& s)
	{
		Identity();
		_11 = s.x_;
		_22 = s.y_;
		_33 = s.z_;
	}

	void Matrix::SetRotationX(float angle)
	{
		auto radian = AngleToRadian(angle);
		auto cos = cosf(radian);
		auto sin = sinf(radian);
		Identity();
		_22 = cos;
		_23 = sin;
		_32 = -sin;
		_33 = cos;
	}

	void Matrix::SetRotationY(float angle)
	{
		auto radian = AngleToRadian(angle);
		auto cos = cosf(radian);
		auto sin = sinf(radian);
		Identity();
		_11 = cos;
		_13 = -sin;
		_31 = sin;
		_33 = cos;
	}

	void Matrix::SetRotationZ(float angle)
	{
		auto radian = AngleToRadian(angle);
		auto cos = cosf(radian);
		auto sin = sinf(radian);
		Identity();
		_11 = cos;
		_12 = sin;
		_21 = -sin;
		_22 = cos;
	}

	void Matrix::SetTranslation(const Vector3& t)
	{
		Identity();
		_41 = t.x_;
		_42 = t.y_;
		_43 = t.z_;
	}

	void Matrix::FromQuaternion(const Quaternion& q)
	{
		auto ww = 2.0f * q.w_;
		auto xx = 2.0f * q.v_.x_;
		auto yy = 2.0f * q.v_.y_;
		auto zz = 2.0f * q.v_.z_;

		_11 = 1.0f - yy * q.v_.y_ - zz * q.v_.z_;
		_12 = xx * q.v_.y_ + ww * q.v_.z_;
		_13 = xx * q.v_.z_ - ww * q.v_.x_;
		_14 = 0.0f;

		_21 = xx * q.v_.y_ - ww * q.v_.z_;
		_22 = 1.0f - xx * q.v_.x_ - zz * q.v_.z_;
		_23 = yy * q.v_.z_ + ww * q.v_.x_;
		_24 = 0.0f;

		_31 = xx * q.v_.z_ + ww * q.v_.y_;
		_32 = yy * q.v_.z_ - ww * q.v_.x_;
		_33 = 1.0f - xx * q.v_.x_ - yy * q.v_.y_;
		_34 = 0.0f;

		_41 = _42 = _43 = 0.0f;
		_44 = 1.0f;
	}

	Quaternion Matrix::ToQuaternion()const
	{
		Quaternion q(0.0f, Vector3());

		q.w_ = sqrtf(_11 + _22 + _33 + 1) / 2;
		q.v_.x_ = (_23 - _32) / (4 * q.w_);
		q.v_.y_ = (_31 - _13) / (4 * q.w_);
		q.v_.z_ = (_12 - _21) / (4 * q.w_);

		return q;
	}

	Vector4 Matrix::ApplyVector4(const Vector4& v)const
	{
		Vector4 ret;
		ret.x_ = v.x_ * _11 + v.y_ * _21 + v.z_ * _31 + v.w_ * _41;
		ret.y_ = v.x_ * _12 + v.y_ * _22 + v.z_ * _32 + v.w_ * _42;
		ret.z_ = v.x_ * _13 + v.y_ * _23 + v.z_ * _33 + v.w_ * _43;
		ret.w_ = v.x_ * _14 + v.y_ * _24 + v.z_ * _34 + v.w_ * _44;
		return ret;
	}

	void Matrix::SetLookAtLH(const Vector3& eye, const Vector3& at, const Vector3& up)
	{
		auto zaxis = at - eye;
		zaxis.normalize();
		auto xaxis = up.crossProduct(zaxis);
		xaxis.normalize();
		auto yaxis = zaxis.crossProduct(xaxis);
		yaxis.normalize();

		_11 = xaxis.x_;
		_12 = yaxis.x_;
		_13 = zaxis.x_;
		_14 = 0.0f;

		_21 = xaxis.y_;
		_22 = yaxis.y_;
		_23 = zaxis.y_;
		_24 = 0.0f;

		_31 = xaxis.z_;
		_32 = yaxis.z_;
		_33 = zaxis.z_;
		_34 = 0.0f;

		_41 = -(xaxis.dotProduct(eye));
		_42 = -(yaxis.dotProduct(eye));
		_43 = -(zaxis.dotProduct(eye));
		_44 = 1.0f;
	}

	void Matrix::SetPerspectiveLH(float w, float h, float zn, float zf)
	{
		_11 = 2 * zn / w;
		_12 = _13 = _14 = 0.0f;

		_22 = 2 * zn / h;
		_21 = _23 = _24 = 0.0f;

		_31 = _32 = 0.0f;
		_33 = zf / (zf - zn);
		_34 = 1.0f;

		_41 = _42 = 0.0f;
		_43 = zn * zf / (zn - zf);
		_44 = 1.0f;
	}

	void Matrix::SetPerspectiveFovLH(float fovy/*radian*/, float aspect, float zn, float zf)
	{
		auto yscale = 1.0f / tanf(fovy / 2);
		auto xscale = yscale / aspect;

		//float    SinFov;
		//float    CosFov;
		//DirectX::XMScalarSinCos(&SinFov, &CosFov, 0.5f * fovy);
		//float yscale = CosFov / SinFov;
		//float xscale = yscale / aspect;


		_11 = xscale;
		_12 = _13 = _14 = 0.0f;

		_22 = yscale;
		_21 = _23 = _24 = 0.0f;

		_31 = _32 = 0.0f;
		_33 = zf / (zf - zn);
		_34 = 1.0f;

		_41 = _42 = 0.0f;
		_43 = -zn * zf / (zf - zn);
		_44 = 0.0f;
	}

	Matrix operator *(float s, const Matrix& mat)
	{
		Matrix ret;
		ret._11 = mat._11 * s; ret._12 = mat._12 * s; ret._13 = mat._13 * s; ret._14 = mat._14 * s;
		ret._21 = mat._21 * s; ret._22 = mat._22 * s; ret._23 = mat._23 * s; ret._24 = mat._24 * s;
		ret._31 = mat._31 * s; ret._32 = mat._32 * s; ret._33 = mat._33 * s; ret._34 = mat._34 * s;
		ret._41 = mat._41 * s; ret._42 = mat._42 * s; ret._43 = mat._43 * s; ret._44 = mat._44 * s;

		return ret;
	}

	Matrix operator *(const Matrix& m1, const Matrix& m2)
	{
		Matrix ret;
		ret._11 = m1._11 * m2._11 + m1._12 * m2._21 + m1._13 * m2._31 + m1._14 * m2._41;
		ret._12 = m1._11 * m2._12 + m1._12 * m2._22 + m1._13 * m2._32 + m1._14 * m2._42;
		ret._13 = m1._11 * m2._13 + m1._12 * m2._23 + m1._13 * m2._33 + m1._14 * m2._43;
		ret._14 = m1._11 * m2._14 + m1._12 * m2._24 + m1._13 * m2._34 + m1._14 * m2._44;

		ret._21 = m1._21 * m2._11 + m1._22 * m2._21 + m1._23 * m2._31 + m1._24 * m2._41;
		ret._22 = m1._21 * m2._12 + m1._22 * m2._22 + m1._23 * m2._32 + m1._24 * m2._42;
		ret._23 = m1._21 * m2._13 + m1._22 * m2._23 + m1._23 * m2._33 + m1._24 * m2._43;
		ret._24 = m1._21 * m2._14 + m1._22 * m2._24 + m1._23 * m2._34 + m1._24 * m2._44;

		ret._31 = m1._31 * m2._11 + m1._32 * m2._21 + m1._33 * m2._31 + m1._34 * m2._41;
		ret._32 = m1._31 * m2._12 + m1._32 * m2._22 + m1._33 * m2._32 + m1._34 * m2._42;
		ret._33 = m1._31 * m2._13 + m1._32 * m2._23 + m1._33 * m2._33 + m1._34 * m2._43;
		ret._34 = m1._31 * m2._14 + m1._32 * m2._24 + m1._33 * m2._34 + m1._34 * m2._44;

		ret._41 = m1._41 * m2._11 + m1._42 * m2._21 + m1._43 * m2._31 + m1._44 * m2._41;
		ret._42 = m1._41 * m2._12 + m1._42 * m2._22 + m1._43 * m2._32 + m1._44 * m2._42;
		ret._43 = m1._41 * m2._13 + m1._42 * m2._23 + m1._43 * m2._33 + m1._44 * m2._43;
		ret._44 = m1._41 * m2._14 + m1._42 * m2._24 + m1._43 * m2._34 + m1._44 * m2._44;

		return ret;
	}
}