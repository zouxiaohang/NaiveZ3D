#include <iostream>

#include "File\Include\IOBJFileMgr.h"
#include "Application\Include\Application.h"

using namespace std;

#define UNITEST

#ifndef UNITEST
int main()
{
	//string file = "Res/EyeBall/eyeball.obj";
	//auto mgr = NaiveZ3D::IOBJFileMgr();
	//auto model = mgr.Load(file);
	std::cout << "................. NaiveZ3D engine init............" << std::endl;
	
	NaiveZ3D::Application app("NaiveZ3D", 1334, 750);
	if (!app.Init())
	{
		app.Terminate();
	}
	app.Run();

	//system("pause");
	return 0;
}

#else

#include <map>
#include <string>
using namespace std;

#include "Core\GLRender\Include\GLShader.h"
using namespace NaiveZ3D;

int main()
{
	std::cout << "................. NaiveZ3D engine unitest............" << std::endl;
	Application app("NaiveZ3D UniTest", 800, 600);
	if (!app.Init())
	{
		app.Terminate();
	}

	auto shader = Shader("UniTest");
	map<string, string> shaders = 
	{
		{"vertex", "Res/Shaders/test.vs"},
		{"fragment", "Res/Shaders/test.fs"},
	};
	auto res = shader.CompileAndLink(shaders);
	if (!res)
	{
		if (shader.GetCompileState() != Shader::ShaderState::SUCC)
		{
			cout << "CompileState: " << shader.GetCompileErrorInfo() << endl;
		}
		else if (shader.GetLinkState() != Shader::ShaderState::SUCC)
		{
			cout << "LinkState: " << shader.GetLinkErrorInfo() << endl;
		}
	}
	else
	{
		shader.Use();
	}

	app.Terminate();
	system("pause");
	return 0;
}

#endif