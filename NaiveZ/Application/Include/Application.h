#pragma once

#include <string>
#include <functional>
#include <memory>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../../Core/GLRender/Include/GLRenderSystem.h"

namespace NaiveZ3D
{
	using KeyCallbackDef = GLFWkeyfun;
	using GLRSPtr = std::unique_ptr<GLRenderSystem>;

	class Application
	{
	public:
		Application(const std::string& appName, GLsizei width, GLsizei height);

		std::string GetAppName()const { return mAppName_; }
		GLFWwindow *GetGlfwWindow()const { return mWindow_; }
		GLsizei GetAppWidth()const { return mWidth_; }
		GLsizei GetAppHeight()const { return mHeight_; }

		bool Init();
		void Terminate();
		void SetKeyCallback(KeyCallbackDef cb);
		void Run();
	private:
		//void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	private:
		std::string mAppName_;
		GLsizei mWidth_;
		GLsizei mHeight_;
		GLFWwindow *mWindow_;
		//GLRenderSystem *mGLRenderSystemPtr_;
		GLRSPtr mGLRenderSystemPtr_;
	};
}