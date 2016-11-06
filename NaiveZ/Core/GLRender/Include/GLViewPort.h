#pragma once

#include <utility>

#include "GL/glew.h"

namespace NaiveZ3D
{
	class ViewPort
	{
	public:
		ViewPort(){}
		ViewPort(std::pair<GLint, GLint> p, GLint w, GLint h)
			:mBegPos_(p),
			mWidth_(w),
			mHeight_(h)
		{}

		GLint GetWidth()const { return mWidth_; }
		GLint GetHeight()const { return mHeight_; }

		void Use() { glViewport(mBegPos_.first, mBegPos_.second, mWidth_, mHeight_); }
	private:
		std::pair<GLint, GLint> mBegPos_;
		GLint mWidth_;
		GLint mHeight_;
	};
}