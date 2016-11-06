#include <iostream>

#include "File\Include\IOBJFileMgr.h"
#include "Application\Include\Application.h"

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
	vector<string> objs = {"Res/Cube/cube.obj"};
	app.LoadAndDraw(objs);
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