#include <iostream>

#include "Include/Application.h"
#include "../Core/GLRender/Include/GLViewPort.h"
#include "../Utils/Include/Constant.h"
#include "../File/Include/IOBJFileMgr.h"

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

namespace NaiveZ3D
{
	Application::Application(const std::string& appName, GLsizei width, GLsizei height)
		:mAppName_(appName),
		mWidth_(width),
		mHeight_(height)
	{
		mGLRenderSystemPtr_ = GLRSPtr(new GLRenderSystem);
	}

	bool Application::Init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		mWindow_ = glfwCreateWindow(mWidth_, mHeight_, mAppName_.c_str(), nullptr, nullptr);
		if (mWindow_ == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			return false;
		}
		glfwMakeContextCurrent(mWindow_);

		SetKeyCallback(KeyCallback);

		auto ret = mGLRenderSystemPtr_->Init(this);
		if (!ret)
		{
			std::cout << "Fail to init GLRenderSystem" << std::endl;
			return false;
		}
		mGLRenderSystemPtr_->SetClearColor(Color::Black);

		return true;
	}

	void Application::Run()
	{
		while (!glfwWindowShouldClose(mWindow_))
		{
			// Check and call events
			glfwPollEvents();

			mGLRenderSystemPtr_->Draw(0);

			glfwSwapBuffers(mWindow_);
		}
	}

	void Application::Terminate()
	{
		glfwTerminate();
	}

	void Application::SetKeyCallback(KeyCallbackDef cb)
	{
		glfwSetKeyCallback(mWindow_, cb);
	}

	void Application::LoadAndDraw(const std::vector<std::string>& objFiles)
	{
		auto loader = IOBJFileMgr();
		for (auto file : objFiles)
		{
			auto model = loader.Load(file);
			mModelMap_[model.GetModelName()] = model;
		}
		mGLRenderSystemPtr_->CommitModel(mModelMap_);
	}
}