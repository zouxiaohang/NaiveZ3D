#include "Include\Camera.h"

NaiveZ3D::Camera::Camera(Vector3 pos, Vector3 target, Vector3 up, Vector3 right)
	:mPos_(pos),
	mTarget_(target),
	mUp_(up),
	mRight_(right)
{
	BuildViewTransform();
}

void NaiveZ3D::Camera::BuildViewTransform()
{
	auto dir = mTarget_ - mPos_;
	dir.normalize();
	mUp_.normalize();
	mRight_ = mUp_.crossProduct(dir);
	mRight_.normalize();
	mUp_ = dir.crossProduct(mRight_);
	mUp_.normalize();
}
