#pragma once

#include <string>
#include <functional>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace NaiveZ3D
{
	using KeyCallbackDef = GLFWkeyfun;

	class Application
	{
	public:
		Application(const std::string& appName, GLsizei width, GLsizei height);

		std::string GetAppName()const { return mAppName_; }

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
	};
}