#include <iostream>

#define GLEW_STATIC
#include "Third\glew-2\include\GL\glew.h"
#include "Third\glfw3.2\include\GLFW\glfw3.h"

#include "File\Include\IOBJFileMgr.h"

using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{
	//string file = "Res/EyeBall/eyeball.obj";
	//auto mgr = NaiveZ3D::IOBJFileMgr();
	//auto model = mgr.Load(file);
	std::cout << "................. NaiveZ3D engine init............" << std::endl;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(1334, 750, "NaiveZ3D", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	while (!glfwWindowShouldClose(window))
	{
		// Check and call events
		glfwPollEvents();

		// Rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap the buffers
		glfwSwapBuffers(window);
	}
	glfwTerminate();

	system("pause");
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}