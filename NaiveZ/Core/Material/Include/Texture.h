#pragma once

#include <string>

#include "GL/glew.h"

namespace NaiveZ3D
{
	class Texture
	{
	public:
		Texture(const std::string& name);

		~Texture();
	public:
		GLuint mTex_;

		GLint mWidth_;
		GLint mHeight_;
	};
}