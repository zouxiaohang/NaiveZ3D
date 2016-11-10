#include "Include\GLShader.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
using namespace std;

namespace NaiveZ3D
{
	Shader::Shader(const std::string& name)
	:mShaderName_(name),
		mCompileState_(ShaderState::NONE),
		mLinkState_(ShaderState::NONE)
	{}

	void Shader::Destroy()
	{
		if (mLinkState_ == ShaderState::SUCC && glIsProgram(mProgram_))
		{
			glDeleteProgram(mProgram_);
			mProgram_ = 0;
		}
	}

	void Shader::Use()
	{
		bool ret = glIsProgram(mProgram_);
		assert(ret);
		if (mCompileState_ == ShaderState::SUCC && mLinkState_ == ShaderState::SUCC)
		{
			glUseProgram(mProgram_);
		}
	}

	bool Shader::CompileAndLink(const map<string, string>& shaders)
	{
		ifstream ifs;
		GLint success;
		GLchar infoLog[512];
		GLuint sh;
		vector<GLuint> vShaders;

		///////// Compile
		for (auto item : shaders)
		{
			if (item.first == "vertex")
			{
				sh = glCreateShader(GL_VERTEX_SHADER);
			}
			else if (item.first == "fragment")
			{
				sh = glCreateShader(GL_FRAGMENT_SHADER);
			}
			else
			{
				continue;
			}

			if (sh == 0 && !glIsShader(sh))
			{
				mCompileState_ = ShaderState::FAIL;
				mCompileErrorInfo_ = "Function 'glCreateShader' can not create a valid shader";
				return false;
			}

			ifs.open(item.second);
			if (!ifs)
			{
				mCompileState_ = ShaderState::FAIL;
				mCompileErrorInfo_ = "Can not open file->" + item.second;
				return false;
			}
			stringstream ss;
			ss << ifs.rdbuf();
			string text = ss.str();
			mSource_[item.first] = text;
				
			const GLchar * str= text.c_str();
			glShaderSource(sh, 1, &str, nullptr);
			glCompileShader(sh);
			glGetShaderiv(sh, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(sh, 512, nullptr, infoLog);
				mCompileState_ = ShaderState::FAIL;
				mCompileErrorInfo_ = infoLog + string("in file->") + item.second;
				return false;
			}
			vShaders.push_back(sh);
			ifs.close();
		}
		mCompileState_ = Shader::ShaderState::SUCC;

		////////// Link
		mProgram_ = glCreateProgram();
		if (mProgram_ == 0 && !glIsProgram(mProgram_))
		{
			mLinkState_ = ShaderState::FAIL;
			mLinkErrorInfo_ = "Function 'glCreateProgram' can not create a valid program";
			return false;
		}
		for (auto sh : vShaders)
		{
			glAttachShader(mProgram_, sh);
			//glDeleteShader(sh);
		}
		glLinkProgram(mProgram_);
		for (auto sh : vShaders)
		{
			glDeleteShader(sh);
		}
		glGetProgramiv(mProgram_, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(mProgram_, 512, nullptr, infoLog);
			mLinkState_ = ShaderState::FAIL;
			mLinkErrorInfo_ = infoLog;
			return false;
		}
		mLinkState_ = ShaderState::SUCC;

		InitUnifrom();

		return true;
	}
	void Shader::InitUnifrom()
	{
		mMVPLoc_ = glGetUniformLocation(mProgram_, "MVP");
		mKdSampler2D_ = glGetUniformLocation(mProgram_, "kdSampler2D");
	}
}