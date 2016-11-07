#include "Include/Camera.h"
#include "../Math/Include/Utils.h"

namespace NaiveZ3D
{
	Camera::Camera(GLMVec3 pos, GLMVec3 target, GLMVec3 up)
		:mPos_(pos),
		mTarget_(target),
		mUp_(up)
	{
		BuildViewTransform();
	}
	void Camera::SetPerspectiveFov(float fovy, float aspect, float zn, float zf)
	{
		mFovy_ = fovy;
		mAspect_ = aspect;
		mZNear_ = zn;
		mZFar_ = zf;

		BuildProjTransform();
	}
	void Camera::SetFovy(float fovy)
	{
		mFovy_ = fovy;
		BuildProjTransform();
	}
	void Camera::SetPos(GLMVec3 pos)
	{
		mPos_ = pos;
		BuildViewTransform();
	}
	void Camera::SetTarget(GLMVec3 target)
	{
		mTarget_ = target;
		BuildViewTransform();
	}
	void Camera::Translate(GLMVec3 trans)
	{
		mPos_ += trans;
		BuildViewTransform();
	}
	void Camera::Rotate(float radians, Axis axis)
	{
		auto axisRotate = GLMVec3();
		auto angle = RadianToAngle(radians);

		if (Axis::X == axis)
			axisRotate = GLMVec3(1, 0, 0);
		else if (Axis::Y == axis)
			axisRotate = GLMVec3(0, 1, 0);
		else if (Axis::Z == axis)
			axisRotate = GLMVec3(0, 0, 1);

		mViewTransfrom_ = glm::rotate(mViewTransfrom_, angle, axisRotate);
	}
	void Camera::BuildViewTransform()
	{
		mUp_ = glm::normalize(mUp_);
		auto dir = mTarget_ - mPos_;
		dir = glm::normalize(dir);
		mRight_ = glm::normalize(glm::cross(dir, mUp_));
		mUp_ = glm::normalize(glm::cross(mRight_, dir));

		mViewTransfrom_ = glm::lookAt(mPos_, mTarget_, mUp_);
	}
	void Camera::BuildProjTransform()
	{
		mProjTransform_ = glm::perspective(mFovy_, mAspect_, mZNear_, mZFar_);
	}
}
