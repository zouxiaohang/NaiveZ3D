#include <iostream>
using namespace std;

#include "Include\GLRenderSystem.h"
#include "Include\GLShaderMgr.h"
#include "../../UniTest/UniTest.h"
#include "../../Application/Include/Application.h"

NaiveZ3D::GLRenderSystem::~GLRenderSystem()
{
	for (auto& model : mGLModelBuffer_)
	{
		model.Destroy();
	}
}

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

	glEnable(GL_DEPTH_TEST);

	return true;
}

void NaiveZ3D::GLRenderSystem::Draw(GLfloat delta)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//暂时这么写
	//TODO:重构
	GLShaderMgr::Instance().UseShader("eyeball");
	glm::mat4 model, view, projection;
	model = glm::rotate(model, (GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(45.0f, 1.0f * mApplication_->GetAppWidth() / mApplication_->GetAppHeight(), 0.1f, 100.0f);
	auto transform = projection * view * model;
	GLShaderMgr::Instance().SetShaderUniform("eyeball", "MVP", transform);
	DrawGLModel();
}

void NaiveZ3D::GLRenderSystem::SetClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	glClearColor(r, g, b, a);
}

void NaiveZ3D::GLRenderSystem::SetClearColor(GLColor c)
{
	glClearColor(c.red, c.green, c.blue, c.alpha);
}

void NaiveZ3D::GLRenderSystem::CommitModel(const ModelMap& map)
{
	CreateGLModelBuffer(map);
}

void NaiveZ3D::GLRenderSystem::SetViewPort(GLint x, GLint y, GLint w, GLint h)
{
	mViewPort_ = ViewPort({ x, y }, w, h);
}

void NaiveZ3D::GLRenderSystem::CreateGLModelBuffer(const ModelMap& modelMap)
{
	for (const auto& kv : modelMap)
	{
		auto model = GLModel(kv.second);
		mGLModelBuffer_.emplace_back(model);
	}
}

void NaiveZ3D::GLRenderSystem::DrawGLModel()
{
	for (auto& model : mGLModelBuffer_)
	{
		model.DrawArrays();
	}
}
