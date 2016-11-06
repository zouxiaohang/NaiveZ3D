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

	private:
		void Init();
		void LoadShaders();

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
}