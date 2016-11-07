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

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	//if (IsFirstMouse)
	//{
	//	auto x = app->GetAppWidth();
	//	x /= 2;
	//	LastX = app->GetAppWidth() / 2;
	//	LastY = app->GetAppHeight() / 2;
	//	IsFirstMouse = false;
	//}
	//auto xoffset = xpos - LastX;
	//auto yoffset = LastY - ypos;
	//LastX = xpos;
	//LastY = ypos;
	//GLfloat sensitivity = 0.05;
	//xoffset *= sensitivity;
	//yoffset *= sensitivity;
	//yaw += xoffset;
	//Pitch += yoffset;

	//if (Pitch > 89.0f)
	//{
	//	Pitch = 89.0f;
	//	std::cout << "pitch 89" << std::endl;
	//}
	//if (Pitch < -89.0f)
	//{
	//	Pitch = -89.0f;
	//	std::cout << "pitch -89" << std::endl;
	//}

	//glm::vec3 front;
	//front.x = cos(glm::radians(yaw)) * cos(glm::radians(Pitch));
	//front.y = sin(glm::radians(Pitch));
	//front.z = sin(glm::radians(yaw)) * cos(glm::radians(Pitch));
	//app->GetCamera().SetTarget(glm::normalize(front));
}
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	//if (gFovy >= 1.0f && gFovy <= 45.0f)
	//	gFovy -= yoffset*0.1;
	//if (gFovy <= 1.0f)
	//	gFovy = 1.0f;
	//if (gFovy >= 45.0f)
	//	gFovy = 45.0f;
	//std::cout << gFovy << std::endl;
	//app->GetCamera().SetFovy(gFovy);
}
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	GLfloat cameraSpeed = 0.5f;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	auto& camera = app->GetCamera();
	auto cameraPos = camera.GetPos();
	auto cameraFront = glm::normalize(camera.GetTarget() - cameraPos);

	if (key == GLFW_KEY_W)
		cameraPos += cameraSpeed * cameraFront;
	if (key == GLFW_KEY_S)
		cameraPos -= cameraSpeed * cameraFront;
	if (key == GLFW_KEY_A)
		cameraPos -= camera.GetRightDir() * cameraSpeed;
	if (key == GLFW_KEY_D)
		cameraPos += camera.GetRightDir() * cameraSpeed;

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