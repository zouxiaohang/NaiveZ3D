#include "IOBJFileMgrUniTest.h"

#include <string>
#include <iostream>
using namespace std;

#include "../File/Include/IOBJFileMgr.h"

bool NaiveZ3D::UniTest::IOBJFileMgrUniTest::Test()
{
	string file = "Res/Cube/cube.obj";
	auto mgr = NaiveZ3D::IOBJFileMgr();
	auto model = mgr.Load(file);
	if (model.MeshSize() == 0)
	{
		SetConsoleColor(ConsoleColor::RED);
		cout << "IOBJFileMgr loads 0 mesh in file " + file << endl;
		SetConsoleColor();

		return false;
	}
	SetConsoleColor(ConsoleColor::GREEN);
	cout << "IOBJFileMgr UniTest Pass" << endl;
	SetConsoleColor();

	return true;
}
