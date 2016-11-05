#pragma once

#include <string>
#include <vector>
#include <map>

#include "GL/glew.h"

namespace NaiveZ3D
{
	class Shader
	{
	public:
		enum class ShaderState
		{
			NONE,
			SUCC,
			FAIL,
		};

		Shader(const std::string& name = "");
		~Shader();

		bool CompileAndLink(const std::map<std::string, std::string>&);

		void Use();

		std::map<std::string, std::string> GetShaderSource()const { return mSource_; }
		std::string GetShaderName()const { return mShaderName_; }

		ShaderState GetCompileState()const { return mCompileState_; }
		std::string GetCompileErrorInfo()const { return mCompileErrorInfo_; }
		ShaderState GetLinkState()const { return mLinkState_; }
		std::string GetLinkErrorInfo()const { return mLinkErrorInfo_; }

	private:
		std::string mShaderName_;
		std::map<std::string, std::string> mSource_;
		GLint mProgram_;
		ShaderState mCompileState_;
		std::string mCompileErrorInfo_;
		ShaderState mLinkState_;
		std::string mLinkErrorInfo_;
	};
}