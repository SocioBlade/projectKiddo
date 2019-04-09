#include <iostream>

#include "glew.h"
#include "glfw3.h"

#include "glm.hpp"
#include "ext.hpp"

#include "GameState.h"

#include "shader.h"

using namespace engineTest;
using namespace graphics;


int main(void)
{
	GLFWwindow* window;
	GameState game;

	/* Initialize the library */
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		printf("ERROR: %s \n", glewGetErrorString(GlewInitResult));
		system("pause");
		exit(EXIT_FAILURE);

	}

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		//Shader redShade("ProjectKiddo v.0.000002/vs.glsl", "ProjectKiddo v.0.000002/fs.glsl");
		Shader shader("VS.glsl","FS.glsl");

		/* Render here */
		game.draw(); //This is a basic openGL draw call - no shaders implemented
		

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}