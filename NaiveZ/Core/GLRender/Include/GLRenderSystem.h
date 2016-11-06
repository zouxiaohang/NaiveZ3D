#pragma once

#include <memory>

#include "GL/glew.h"

#include "GLShaderMgr.h"
#include "GLViewPort.h"
//#include "../../../Application/Include/Application.h"

namespace NaiveZ3D
{
	class Application;

	class GLRenderSystem
	{
	public:
		bool Init(Application* app);
		void Run(GLfloat delta);
	private:
		void SetViewPort(GLint x, GLint y, GLint w, GLint h);

	private:
		Application* mApplication_;
		ViewPort mViewPort_;
	};
}