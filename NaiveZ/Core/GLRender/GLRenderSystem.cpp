#include <iostream>
using namespace std;

#include "Include\GLRenderSystem.h"
#include "../../UniTest/UniTest.h"
#include "../../Application/Include/Application.h"

bool NaiveZ3D::GLRenderSystem::Init(Application* app)
{
	mApplication_ = app;

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return false;
	}

	auto width = app->GetAppWidth();
	auto height = app->GetAppHeight();
	glfwGetFramebufferSize(app->GetGlfwWindow(), &width, &height);
	SetViewPort(0, 0, width, height);
	mViewPort_.Use();
	return true;
}

void NaiveZ3D::GLRenderSystem::Run(GLfloat delta)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void NaiveZ3D::GLRenderSystem::SetViewPort(GLint x, GLint y, GLint w, GLint h)
{
	mViewPort_ = ViewPort({ x, y }, w, h);
}
