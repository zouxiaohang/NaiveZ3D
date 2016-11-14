#include "Include\SunLight.h"

void NaiveZ3D::SunLight::SetColor(Vector3 c)
{
	mColor_ = c;
}

NaiveZ3D::Vector3 NaiveZ3D::SunLight::GetColor() const
{
	return mColor_;
}

void NaiveZ3D::SunLight::SetDir(Vector3 d)
{
	mDir_ = d;
}

NaiveZ3D::Vector3 NaiveZ3D::SunLight::GetDir() const
{
	return mDir_;
}
