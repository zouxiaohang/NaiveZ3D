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
		void SetShaderUniformMatrix(const std::string& shaderName, const std::string& uniform, const T& value);
		template<class T>
		void SetUniformByNameMatrix(const std::string& uniform, const T& value);

		template<class T>
		void SetShaderUniformFI(const std::string& shaderName, const std::string& uniform, const T& value);
		template<class T>
		void SetUniformFIByName(const std::string& uniform, const T& value);

		template<class T>
		void SetShaderUniformVector(const std::string& shaderName, const std::string& uniform, const T& value);
		template<class T>
		void SetUniformVByName(const std::string& uniform, const T& value);

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
		std::string mCurShaderName_;

	private:
		ShaderCache mShaderCache_;
	};

	template<class T>
	inline void GLShaderMgr::SetShaderUniformMatrix(const std::string & shaderName, const std::string & uniform, const T & value)
	{
		auto& shader = GetShaderByName(shaderName);
		shader.SetUniformMatrixByName(uniform, value);
	}
	template<class T>
	inline void GLShaderMgr::SetUniformByNameMatrix(const std::string & uniform, const T & value)
	{
		SetShaderUniformMatrix(mCurShaderName_, uniform, value);
	}
	template<class T>
	inline void GLShaderMgr::SetShaderUniformFI(const std::string & shaderName, const std::string & uniform, const T & value)
	{
		auto& shader = GetShaderByName(shaderName);
		shader.SetUniformFIByName(uniform, value);
	}
	template<class T>
	inline void GLShaderMgr::SetUniformFIByName(const std::string & uniform, const T & value)
	{
		SetShaderUniformFI(mCurShaderName_, uniform, value);
	}
	template<class T>
	inline void GLShaderMgr::SetShaderUniformVector(const std::string & shaderName, const std::string & uniform, const T & value)
	{
		auto& shader = GetShaderByName(shaderName);
		shader.SetUniformVByName(uniform, value);
	}
	template<class T>
	inline void GLShaderMgr::SetUniformVByName(const std::string & uniform, const T & value)
	{
		SetShaderUniformVector(mCurShaderName_, uniform, value);
	}
}