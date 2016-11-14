#pragma once

#include <vector>
#include <map>
#include <string>

#include "GL/glew.h"

#include "GLViewPort.h"
#include "GLColor.h"
#include "../../../File/Include/Model.h"
#include "GLModel.h"
#include "../../Light/Include/SunLight.h"
#include "../../Light/Include/PointLight.h"

namespace NaiveZ3D
{
	class Application;
	using GLModelBuffer = std::vector<GLModel>;
	using ModelMap = std::map<std::string, Model>;

	class GLRenderSystem
	{
	public:
		~GLRenderSystem();

		bool Init(Application* app);
		void Draw(GLfloat delta);

	public:
		void SetClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0);
		void SetClearColor(GLColor c);
		void CommitModel(const ModelMap& map);
		void SetSunLight(Vector3 pos, Vector3 color = Vector3(1, 1, 1));

	private:
		void SetViewPort(GLint x, GLint y, GLint w, GLint h);
		void CreateGLModelBuffer(const ModelMap&);
		void DrawGLModel();

	private:
		Application* mApplication_;
		ViewPort mViewPort_;
		GLModelBuffer mGLModelBuffer_;

		////// π‚‘¥ //////
		SunLightPtr mSunLight_;
		PointLightPtr mPointLights_[5];
	};
}