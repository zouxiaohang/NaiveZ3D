#include "ShaderUniTest.h"

#include <map>
#include <string>
#include <iostream>
using namespace std;

#include "../Application/Include/Application.h"
#include "../Core/GLRender/Include/GLShader.h"

bool NaiveZ3D::UniTest::ShaderUniTest::Test()
{
	Application app("NaiveZ3D Shader UniTest", 800, 600);
	if (!app.Init())
	{
		app.Terminate();
	}

	auto shader = Shader("ShaderUniTest");
	map<string, string> shaders =
	{
		{ "vertex", "Res/Shaders/test.vs" },
		{ "fragment", "Res/Shaders/test.fs" },
	};
	auto res = shader.CompileAndLink(shaders);
	if (!res)
	{
		if (shader.GetCompileState() != Shader::ShaderState::SUCC)
		{
			SetConsoleColor(ConsoleColor::RED);
			cout << "CompileState: " << shader.GetCompileErrorInfo() << endl;
			SetConsoleColor();

			return false;
		}
		else if (shader.GetLinkState() != Shader::ShaderState::SUCC)
		{
			SetConsoleColor(ConsoleColor::RED);
			cout << "LinkState: " << shader.GetLinkErrorInfo() << endl;
			SetConsoleColor();

			return false;
		}
	}
	else
	{
		shader.Use();
	}
	app.Terminate();
	SetConsoleColor(ConsoleColor::GREEN);
	cout << "Shader UniTest Pass" << endl;
	SetConsoleColor();

	return true;
}
