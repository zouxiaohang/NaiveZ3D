#include "Include/GLRenderSystem.h"
#include "Include/GLShaderMgr.h"
#include "../../UniTest/UniTest.h"
#include "../../Application/Include/Application.h"
#include "../../Logger/Include/LoggerMgr.h"

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
		LoggerMgr::Instance().Error("Failed to initialize GLEW");
		return false;
	}

	auto width = app->GetAppWidth();
	auto height = app->GetAppHeight();
	glfwGetFramebufferSize(app->GetGlfwWindow(), &width, &height);
	SetViewPort(0, 0, width, height);
	mViewPort_.Use();

	//开启深度测试
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	return true;
}

void NaiveZ3D::GLRenderSystem::Draw(GLfloat delta)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//暂时这么写
	//TODO:重构
	GLShaderMgr::Instance().UseShader("eyeball");
	glm::mat4 model, view, projection;
	model = glm::translate(model, glm::vec3(0, 0, -20));
	model = glm::rotate(model, (GLfloat)glfwGetTime() * 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	//GLShaderMgr::Instance().SetShaderUniformMatrix("eyeball", "M", model);
	//GLShaderMgr::Instance().SetShaderUniformMatrix("eyeball", "M_Normal", model);
	auto transform = mApplication_->GetCamera().GetVPTransform() * model;
	GLShaderMgr::Instance().SetShaderUniformMatrix("eyeball", "MVP", transform);
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
		mGLModelBuffer_.emplace_back(GLModel(kv.second));
	}
}

void NaiveZ3D::GLRenderSystem::DrawGLModel()
{
	for (const auto& model : mGLModelBuffer_)
	{
		model.Draw();
	}
}
