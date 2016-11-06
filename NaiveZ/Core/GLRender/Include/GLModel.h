#pragma once

#include <vector>

#include "GL/glew.h"

#include "GLShader.h"
#include "../../../Math/Include/Vector.h"

namespace NaiveZ3D
{
	class Model;
	using Buffer = std::vector<GLuint>;

	struct GLVertexData
	{
		GLVertexData(const Vector3& v)
		{
			x_ = v.x_;
			y_ = v.y_;
			z_ = v.z_;
		}

		GLfloat x_, y_, z_;
	};
	using GLVertexDataBufferBuffer = std::vector<std::vector<GLVertexData>>;

	class GLModel
	{
	public:
		GLModel(const Model&);
		
		void Destroy();

		void DrawArrays();

	private:
		Buffer mVAOBuffer_;
		Buffer mVBOBuffer_;
		Buffer mProgramBuffer_;
		GLVertexDataBufferBuffer mGLVertexDataBufferBuffer_;
	};
}