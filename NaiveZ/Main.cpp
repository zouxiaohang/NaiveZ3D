#include <iostream>

#include "Application/Include/Application.h"
#include "Logger/Include/LoggerMgr.h"

using namespace std;

//#define UNITEST

#ifndef UNITEST
int main()
{
#ifdef _DEBUG
	NaiveZ3D::LoggerMgr::Instance().SetLogLevel(NaiveZ3D::LoggerMgr::Level::Debug);
#else
	NaiveZ3D::LoggerMgr::Instance().SetLogLevel(NaiveZ3D::LoggerMgr::Level::Info);
#endif

	NaiveZ3D::LoggerMgr::Instance().Info("................. NaiveZ3D engine init............");
	
	NaiveZ3D::Application app("NaiveZ3D", 1334, 750);
	if (!app.Init())
	{
		app.Terminate();
	}

	auto eyeball = "Res/EyeBall/eyeball.obj";
	auto cube = "Res/Cube/cube.obj";
	auto bunny = "Res/Bunny/bunny.obj";
	auto diablo = "Res/Diablo/Diablo.obj";
	vector<string> objs = { cube };
	app.LoadAndDraw(objs);
	app.SetCamera(GLMVec3(0, 0, -25), GLMVec3(0, 0, 0), GLMVec3(0, 1, 0), 45.0f, 0.1f, 1000.0f);
	app.Run();

	NaiveZ3D::LoggerMgr::Instance().Info("................. NaiveZ3D engine exit............");
	//system("pause");
	return 0;
}

#else
#include "UniTest\ShaderUniTest.h"
#include "UniTest\IOBJFileMgrUniTest.h"
#include "UniTest\LoggerMgrUniTest.h"
#include "Utils\Include\Helper.h"

int main()
{
	std::cout << "................. NaiveZ3D engine unitest............" << std::endl;
	
	ZAssert(NaiveZ3D::UniTest::ShaderUniTest::Test(), "ShaderUniTest Fail");
	ZAssert(NaiveZ3D::UniTest::IOBJFileMgrUniTest::Test(), "IOBJFileMgrUniTest Fail");
	ZAssert(NaiveZ3D::UniTest::LoggerMgrUniTest::Test(), "LoggerMgrUniTest Fail");

	system("pause");
	return 0;
}

#endif