#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../../Core/GLRender/Include/GLRenderSystem.h"
#include "../../File/Include/Model.h"
#include "../../Camera/Include/Camera.h"
#include "../../Math/Include/Vector.h"

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

		void SetCamera(Vector3 pos, Vector3 target, Vector3 up = Vector3(0,1,0), Vector3 right = Vector3(1,0,0));

	private:
		std::string mAppName_;
		GLsizei mWidth_;
		GLsizei mHeight_;
		GLFWwindow *mWindow_;
		GLRSPtr mGLRenderSystemPtr_;
		ModelMap mModelMap_;
		Camera mCamera_;
	};
}