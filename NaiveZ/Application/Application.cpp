#include <iostream>

#include "Include\Application.h"
#include "../Core/GLRender/Include/GLViewPort.h"

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

namespace NaiveZ3D
{
	//void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

	Application::Application(const std::string& appName, GLsizei width, GLsizei height)
		:mAppName_(appName),
		mWidth_(width),
		mHeight_(height)
	{

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

		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialize GLEW" << std::endl;
			return false;
		}

		glfwGetFramebufferSize(mWindow_, &mWidth_, &mHeight_);
		//glViewport(0, 0, mWidth_, mHeight_);
		auto vp = ViewPort({ 0, 0 }, mWidth_, mHeight_);
		vp.Use();

		return true;
	}

	void Application::Run()
	{
		while (!glfwWindowShouldClose(mWindow_))
		{
			// Check and call events
			glfwPollEvents();

			// Rendering commands here
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Swap the buffers
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
}