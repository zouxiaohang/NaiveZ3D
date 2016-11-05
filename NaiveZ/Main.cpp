#include <iostream>

#include "Third\glfw3.2\include\GLFW\glfw3.h"

#include "File\Include\IOBJFileMgr.h"

using namespace std;

int main()
{
	string file = "Res/EyeBall/eyeball.obj";
	auto mgr = NaiveZ3D::IOBJFileMgr();
	auto model = mgr.Load(file);

	system("pause");
	return 0;
}