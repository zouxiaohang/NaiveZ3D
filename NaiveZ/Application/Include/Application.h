#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../../Core/GLRender/Include/GLRenderSystem.h"
#include "../../File/Include/Model.h"

namespace NaiveZ3D
{
	using KeyCallbackDef = GLFWkeyfun;
	using GLRSPtr = std::unique_ptr<GLRenderSystem>;
	using ModelMap = std::map<std::string, Model>;

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
		void LoadAndDraw(const std::vector<std::string>&);
		void Run();

	private:
		std::string mAppName_;
		GLsizei mWidth_;
		GLsizei mHeight_;
		GLFWwindow *mWindow_;
		GLRSPtr mGLRenderSystemPtr_;
		ModelMap mModelMap_;
	};
}