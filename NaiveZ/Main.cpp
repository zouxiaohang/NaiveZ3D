#include <iostream>

#include "File\Include\IOBJFileMgr.h"
#include "Application\Include\Application.h"

using namespace std;

//#define UNITEST

#ifndef UNITEST
int main()
{
	//string file = "Res/EyeBall/eyeball.obj";
	//auto mgr = NaiveZ3D::IOBJFileMgr();
	//auto model = mgr.Load(file);
	cout << "................. NaiveZ3D engine init............" << endl;
	
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
#include <cassert>
using namespace std;

#include "UniTest\ShaderUniTest.h"

int main()
{
	std::cout << "................. NaiveZ3D engine unitest............" << std::endl;
	
	assert(NaiveZ3D::UniTest::ShaderUniTest::Test(), "ShaderUniTest");

	system("pause");
	return 0;
}

#endif