#pragma once

#include <map>
#include <string>

#include "GLShader.h"

namespace NaiveZ3D
{
	using ShaderCache = std::map<std::string, Shader>;
	class GLShaderMgr
	{
	public:
		static GLShaderMgr& Instance();

	public:
		void UseShader(const std::string&);
		template<class T>
		void SetShaderUniform(const std::string& shaderName, const std::string& uniform, const T& value);

	private:
		void Init();
		void LoadShaders();
		Shader& GetShaderByName(const std::string& name);

	private:
		GLShaderMgr()
		:mInited(false)
		{}

		~GLShaderMgr()
		{
			for (auto& kv : mShaderCache_)
			{
				kv.second.Destroy();
			}
		}

		GLShaderMgr(const GLShaderMgr&);

		bool IsValid()const { return mInited; }
	private:
		bool mInited;

	private:
		ShaderCache mShaderCache_;
	};

	template<class T>
	inline void GLShaderMgr::SetShaderUniform(const std::string & shaderName, const std::string & uniform, const T & value)
	{
		auto& shader = GetShaderByName(shaderName);
		shader.SetUniformByName(uniform, value);
	}
}