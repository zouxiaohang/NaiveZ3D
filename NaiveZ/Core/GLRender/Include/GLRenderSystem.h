#pragma once

#include <memory>

#include "GL/glew.h"

#include "GLShaderMgr.h"
#include "GLViewPort.h"
#include "GLColor.h"

namespace NaiveZ3D
{
	class Application;

	class GLRenderSystem
	{
	public:
		bool Init(Application* app);
		void Run(GLfloat delta);
	public:
		void SetClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0);
		void SetClearColor(GLColor c);
	private:
		void SetViewPort(GLint x, GLint y, GLint w, GLint h);

	private:
		Application* mApplication_;
		ViewPort mViewPort_;
	};
}