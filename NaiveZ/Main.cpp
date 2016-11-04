#include <iostream>

#include "File\Include\IOBJFileMgr.h"

using namespace std;
using namespace NaiveZ3D;

int main()
{
	string file = "Res/EyeBall/eyeball.obj";
	auto mgr = IOBJFileMgr();
	auto model = mgr.Load(file);

	system("pause");
	return 0;
}