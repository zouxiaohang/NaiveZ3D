#pragma once

#include <string>
#include <map>

#include "GL/glew.h"
#include "glm/glm_include.h"
#include "../../../Utils/Include/Helper.h"

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
		//~Shader();
		void Destroy();

		bool CompileAndLink(const std::map<std::string, std::string>&);

		void Use();
		template<class T>
		void SetUniformMatrixByName(const std::string& name, const T& value);
		template<class T >
		void SetUniformFIByName(const std::string& name, const T& value);
		template<class T>
		void SetUniformVByName(const std::string& name, const T& value);

		std::map<std::string, std::string> GetShaderSource()const { return mSource_; }
		std::string GetShaderName()const { return mShaderName_; }

		ShaderState GetCompileState()const { return mCompileState_; }
		std::string GetCompileErrorInfo()const { return mCompileErrorInfo_; }
		ShaderState GetLinkState()const { return mLinkState_; }
		std::string GetLinkErrorInfo()const { return mLinkErrorInfo_; }
	private:
		void InitUnifrom();

	private:
		std::string mShaderName_;
		std::map<std::string, std::string> mSource_;
		GLuint mProgram_;
		ShaderState mCompileState_;
		std::string mCompileErrorInfo_;
		ShaderState mLinkState_;
		std::string mLinkErrorInfo_;

		GLuint mMVPLoc_;
		GLuint mMLoc_;
		GLuint mMNormalLoc_;

		GLuint mKdSampler2D_;
		GLuint mUseTex_;

		GLuint mSunLightDirWLoc_;
		GLuint mSunLightColorLoc_;
	};

	template<class T>
	inline void Shader::SetUniformMatrixByName(const std::string& name, const T & value)
	{
		GLuint loc = -1;
		if (name == "MVP")
			loc = mMVPLoc_;
		else if (name == "M")
			loc = mMLoc_;
		else if (name == "M_Normal")
			loc = mMNormalLoc_;

		ZAssert(loc != -1, "can not find uniform "+name);
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
	}
	template<class T>
	inline void Shader::SetUniformFIByName(const std::string & name, const T & value)
	{
		if (name == "kdSampler2D")
		{
			glUniform1i(mKdSampler2D_, value);
		}
		else if (name == "UseTex")
		{
			glUniform1i(mUseTex_, value);
		}
	}
	template<class T>
	inline void Shader::SetUniformVByName(const std::string & name, const T & value)
	{
		if (name == "SunLightDirW")
		{
			glUniform3f(mSunLightDirWLoc_, value.x_, value.y_, value.z_);
		}
		else if (name == "SunLightColor")
		{
			glUniform3f(mSunLightColorLoc_, value.x_, value.y_, value.z_);
		}
	}
}