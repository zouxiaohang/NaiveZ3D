#pragma once

#include "glm/glm_include.h"

namespace NaiveZ3D
{
	class Camera
	{
	public:
		enum class Axis
		{
			X,
			Y,
			Z,
		};
	public:
		Camera(){}
		Camera(GLMVec3 pos, GLMVec3 target, GLMVec3 up);

		void SetPerspectiveFov(float fovy, float aspect, float zn, float zf);
		void SetFovy(float fovy);

		//¾ø¶Ô
		void SetPos(GLMVec3 pos);
		GLMVec3 GetPos()const { return mPos_; }
		void SetTarget(GLMVec3 target);
		GLMVec3 GetTarget()const { return mTarget_; }

		GLMVec3 GetUpDir()const { return mUp_; }
		GLMVec3 GetRightDir()const { return mRight_; }
		float GetFovy()const { return mFovy_; }

		//Ïà¶Ô
		void Translate(GLMVec3 trans);
		//object space
		void Rotate(float radians, Axis axis);

		GLMMat4 GetViewTransfrom()const { return mViewTransfrom_; }
		GLMMat4 GetProjTransform()const { return mProjTransform_; }
		GLMMat4 GetVPTransform()const { return mProjTransform_ * mViewTransfrom_; }

	private:
		void BuildViewTransform();
		void BuildProjTransform();

	private:
		GLMVec3 mPos_;
		GLMVec3 mTarget_;
		GLMVec3 mUp_;
		GLMVec3 mRight_;
		
		float mFovy_;
		float mAspect_;
		float mZNear_;
		float mZFar_;

		GLMMat4 mViewTransfrom_;
		GLMMat4 mProjTransform_;
		//GLMMat4 mVPTransform_;
	};
}