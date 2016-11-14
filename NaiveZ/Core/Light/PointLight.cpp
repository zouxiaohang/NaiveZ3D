#include "Include\PointLight.h"

NaiveZ3D::PointLight::PointLight(const PointLight &p)
{
	mPosition_ = p.mPosition_;
	mColor_ = p.mColor_;
	mRange_ = p.mRange_;
	mConstAtten_ = p.mConstAtten_;
	mLinearAtten_ = p.mLinearAtten_;
	mQuadAtten_ = p.mQuadAtten_;
}
