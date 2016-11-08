#include <iostream>

#include "Include/Application.h"
#include "../Core/GLRender/Include/GLViewPort.h"
#include "../Utils/Include/Constant.h"
#include "../File/Include/IOBJFileMgr.h"

NaiveZ3D::Application* app;

bool IsFirstMouse = true;
GLfloat gLastX, gLastY;
GLfloat gYaw = -90.0f;
GLfloat gPitch = 0.0f;
GLfloat gFovy = 45.0f;
GLfloat gCameraSpeed = 0.5f;

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	//if (IsFirstMouse)
	//{
	//	auto x = app->GetAppWidth();
	//	x /= 2;
	//	gLastX = app->GetAppWidth() / 2;
	//	gLastY = app->GetAppHeight() / 2;
	//	IsFirstMouse = false;
	//}
	//auto xoffset = xpos - gLastX;
	//auto yoffset = gLastY - ypos;
	//gLastX = xpos;
	//gLastY = ypos;
	//GLfloat sensitivity = 0.05;
	//xoffset *= sensitivity;
	//yoffset *= sensitivity;
	//gYaw += xoffset;
	//gPitch += yoffset;

	//if (gPitch > 89.0f)
	//{
	//	gPitch = 89.0f;
	//	std::cout << "pitch 89" << std::endl;
	//}
	//if (gPitch < -89.0f)
	//{
	//	gPitch = -89.0f;
	//	std::cout << "pitch -89" << std::endl;
	//}

	//glm::vec3 front;
	//front.x = cos(glm::radians(gYaw)) * cos(glm::radians(gPitch));
	//front.y = sin(glm::radians(gPitch));
	//front.z = sin(glm::radians(gYaw)) * cos(glm::radians(gPitch));
	//app->GetCamera().SetTarget(glm::normalize(front));
}
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	auto& camera = app->GetCamera();
	auto cameraPos = camera.GetPos();
	auto cameraUp = camera.GetUpDir();

	cameraPos += (float)yoffset * gCameraSpeed * cameraUp;
	camera.SetPos(cameraPos);
}
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	auto& camera = app->GetCamera();
	auto cameraPos = camera.GetPos();
	auto cameraFront = glm::normalize(camera.GetTarget() - cameraPos);

	if (key == GLFW_KEY_W)
		cameraPos += gCameraSpeed * cameraFront;
	if (key == GLFW_KEY_S)
		cameraPos -= gCameraSpeed * cameraFront;
	if (key == GLFW_KEY_A)
		cameraPos -= camera.GetRightDir() * gCameraSpeed;
	if (key == GLFW_KEY_D)
		cameraPos += camera.GetRightDir() * gCameraSpeed;

	camera.SetPos(cameraPos);
}

namespace NaiveZ3D
{
	Application::Application(const std::string& appName, GLsizei width, GLsizei height)
		:mAppName_(appName),
		mWidth_(width),
		mHeight_(height)
	{
		mGLRenderSystemPtr_ = GLRSPtr(new GLRenderSystem);

		app = this;
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

		//glfwSetInputMode(mWindow_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetScrollCallback(mWindow_, ScrollCallback);
		glfwSetCursorPosCallback(mWindow_, MouseCallback);
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
			glfwPollEvents();

			mGLRenderSystemPtr_->Draw(0);

			glfwSwapBuffers(mWindow_);
		}
	}

	void Application::SetCamera(GLMVec3 pos, GLMVec3 target, GLMVec3 up, float fovy, float zn, float zf)
	{
		mCamera_ = Camera(pos, target, up);
		mCamera_.SetPerspectiveFov(fovy, 1.0f*mWidth_/mHeight_, zn, zf);
		gFovy = mCamera_.GetFovy();
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