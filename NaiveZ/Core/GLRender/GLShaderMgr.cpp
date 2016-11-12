#include <cassert>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <unordered_set>
using namespace std;

#include <Windows.h>

#include "Include/GLShaderMgr.h"
#include "../../UniTest/UniTest.h"
#include "../../Logger/Include/LoggerMgr.h"

namespace
{
	string TrimString(const std::string & str)
	{
		string ret;
		int s = str.find_first_not_of(" ");
		int e = str.find_last_not_of(" ");
		ret = str.substr(s, e - s + 1);
		return ret;
	}

	pair<string, string> ParseFileName(const string& file)
	{
		auto pos = TrimString(file).rfind('.');
		return make_pair<string, string>(file.substr(0, pos), file.substr(pos + 1, file.size() - pos));
	}

	map<string, std::map<std::string, std::string>> DirShaders(const string& path)
	{
		map<string, std::map<std::string, std::string>> shaders;

		string szPath = path;
		std::string szFile;
		std::string szFind;
		WIN32_FIND_DATA FindFileData;
		szFind += szPath + "*.*";
		HANDLE hFind = ::FindFirstFile(szFind.c_str(), &FindFileData);
		if (INVALID_HANDLE_VALUE == hFind)
			return shaders;

		while (true)
		{
			if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				if (FindFileData.cFileName != string("ShaderConfig"))
				{
					auto filePair = ParseFileName(FindFileData.cFileName);
					auto fileName = filePair.first;
					auto fileExt = filePair.second;
					string shaderCategory;
					if (fileExt == "vs")
					{
						shaderCategory = "vertex";
					}
					else if (fileExt == "fs")
					{
						shaderCategory = "fragment";
					}
					shaders[fileName][shaderCategory] = path + FindFileData.cFileName;
				}
			}
			if (!FindNextFile(hFind, &FindFileData))
				break;
		}

		FindClose(hFind);
		return shaders;
	}

	string ParseConfigLine(const string& line)
	{
		auto pos = line.rfind('=');
		auto file = TrimString(line.substr(pos + 1, line.size() - pos));
		return file;
	}
}

NaiveZ3D::GLShaderMgr & NaiveZ3D::GLShaderMgr::Instance()
{
	static GLShaderMgr self;

	if (!self.IsValid())
	{
		self.Init();
	}

	return self;
}

void NaiveZ3D::GLShaderMgr::LoadShaders()
{
	string filePath = "Res/Shaders/";
	ifstream config(filePath + "ShaderConfig");
	auto loadShaders = DirShaders(filePath);
	unordered_set<string> ignoredShaders;
	
	if (config)
	{
		stringstream ss;
		ss << config.rdbuf();
		string line;
		while (ss >> line)
		{
			line = TrimString(line);
			if (line[0] == '#')
			{
				continue;
			}
			auto ignored = ParseConfigLine(line);
			ignoredShaders.insert(ignored);
		}
		config.close();
	}

	for (const auto& kv : loadShaders)
	{
		auto& name = kv.first;
		if (ignoredShaders.count(name) != 0)
			continue;
		auto shader = Shader(name);
		auto ret = shader.CompileAndLink(kv.second);
		if (!ret)
		{
			if (shader.GetCompileState() != Shader::ShaderState::SUCC)
			{
				LoggerMgr::Instance().Error("CompileState: " + shader.GetCompileErrorInfo());
				assert(false);
			}
			else if (shader.GetLinkState() != Shader::ShaderState::SUCC)
			{
				LoggerMgr::Instance().Error("LinkState: " + shader.GetLinkErrorInfo());
				assert(false);
			}
		}
		else
		{
			mShaderCache_[name] = move(shader);
		}
	}
}

NaiveZ3D::Shader & NaiveZ3D::GLShaderMgr::GetShaderByName(const std::string & name)
{
	return mShaderCache_[name];
}

void NaiveZ3D::GLShaderMgr::UseShader(const std::string &name)
{
	auto shader = mShaderCache_.find(name);
	assert(shader != mShaderCache_.end());
	shader->second.Use();
	mCurShaderName_ = name;
}

void NaiveZ3D::GLShaderMgr::Init()
{
	LoadShaders();
	mInited = true;
}
