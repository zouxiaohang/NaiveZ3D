#include <iostream>

#include "File\Include\IOBJFileMgr.h"
#include "Application\Include\Application.h"
#include "glm/glm_include.h"

using namespace std;

//#define UNITEST

#ifndef UNITEST
int main()
{
	cout << "................. NaiveZ3D engine init............" << endl;
	
	NaiveZ3D::Application app("NaiveZ3D", 1334, 750);
	if (!app.Init())
	{
		app.Terminate();
	}

	auto eyeball = "Res/EyeBall/eyeball.obj";
	auto cube = "Res/Cube/cube.obj";
	auto bunny = "Res/Bunny/bunny.obj";
	auto ironman = "Res/IronMan/IronMan.obj";
	vector<string> objs = { eyeball };
	app.LoadAndDraw(objs);
	app.SetCamera(GLMVec3(0, 0, -50), GLMVec3(0, 0, 0), GLMVec3(0, 1, 0), 45.0f, 0.1f, 1000.0f);
	app.Run();

	//system("pause");
	return 0;
}

#else
#include <map>
#include <string>
#include <cassert>
using namespace std;

#include "UniTest\ShaderUniTest.h"
#include "UniTest\IOBJFileMgrUniTest.h"

int main()
{
	std::cout << "................. NaiveZ3D engine unitest............" << std::endl;
	
	assert(NaiveZ3D::UniTest::ShaderUniTest::Test(), "ShaderUniTest");
	assert(NaiveZ3D::UniTest::IOBJFileMgrUniTest::Test(), "IOBJFileMgrUniTest");

	system("pause");
	return 0;
}

#endif