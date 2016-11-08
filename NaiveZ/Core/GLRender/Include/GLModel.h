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

		//GLVertexData(const Vector3& v, const Vector2& tex)
		//{
		//	x_ = v.x_;
		//	y_ = v.y_;
		//	z_ = v.z_;

		//	s_ = tex.x_;
		//	t_ = tex.y_;
		//}

		//GLfloat x_, y_, z_;
		//GLfloat s_, t_;
	};
	using GLVertexDataBufferBuffer = std::vector<std::vector<GLVertexData>>;

	class GLModel
	{
	public:
		GLModel(const Model&);
		
		void Destroy();
		void Draw();

	private:
		void DrawArrays();
		void DrawElements();

	private:
		Buffer mVAOBuffer_;
		Buffer mVBOBuffer_;
		Buffer mEBOBuffer_;
		std::vector<size_t> mEBOSizeBuffer_;
		Buffer mProgramBuffer_;
		GLVertexDataBufferBuffer mGLVertexDataBufferBuffer_;
	};
}