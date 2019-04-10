#include <iostream>
#include <windows.h>

#include "glew.h"
#include "glfw3.h"

#include "glm.hpp"
#include "ext.hpp"

#include "GameState.h"

#include "shader.h"

using namespace engineTest;
using namespace graphics;

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

//~~ Global variables right now, this should be changed.
GLuint gVertexBuffer = 0;
GLuint gVertexAttribute = 0;
GLuint shaderID = 0;


void CreateTriangleData()
{

	struct TriangleVertex
	{
		float x, y, z;
		float r, g, b;
	};

	// create the actual data in plane Z = 0
	// This is called an Array of Structs (AoS) because we will 
	// end up with an array of many of these structs.
	TriangleVertex triangleVertices[3] =
	{
		// pos and color for each vertex
		{ 0.0f, 0.5f, 0.3f,	1.0f, 0.0f, 0.0f},
		{ 0.5f, -0.5f, 0.3f, 1.0f, 0.0f, 0.0f},
		{ -0.5f, -0.5f, 0.3f, 1.0f, 0.0f, 0.0f}
	};

	// Vertex Array Object (VAO), description of the inputs to the GPU 
	glGenVertexArrays(1, &gVertexAttribute);
	// bind is like "enabling" the object to use it
	glBindVertexArray(gVertexAttribute);
	// this activates the first and second attributes of this VAO
	// think of "attributes" as inputs to the Vertex Shader
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// create a vertex buffer object (VBO) id (out Array of Structs on the GPU side)
	glGenBuffers(1, &gVertexBuffer);

	// Bind the buffer ID as an ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, gVertexBuffer);

	// This "could" imply copying to the GPU, depending on what the driver wants to do, and
	// the last argument (read the docs!)
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

	// query which "slot" corresponds to the input vertex_position in the Vertex Shader 
	GLint vertexPos = glGetAttribLocation(shaderID, "vertex_position");
	// if this returns -1, it means there is a problem, and the program will likely crash.
	// examples: the name is different or missing in the shader

	if (vertexPos == -1) {
		std::cout << "VertexPos is wrong" << std::endl;
	}

	// tell OpenGL about layout in memory (input assembler information)
	glVertexAttribPointer(
		vertexPos,				// location in shader
		3,						// how many elements of type (see next argument)
		GL_FLOAT,				// type of each element
		GL_FALSE,				// integers will be normalized to [-1,1] or [0,1] when read...
		sizeof(TriangleVertex), // distance between two vertices in memory (stride)
		BUFFER_OFFSET(0)		// offset of FIRST vertex in the list.
	);

	/*repeat the process for the second attribute.
	query which "slot" corresponds to the input vertex_color in the Vertex Shader */
	GLuint vertexColor = glGetAttribLocation(shaderID, "uv_coords");
	glVertexAttribPointer(
		vertexColor,
		3,
		GL_FLOAT,
		GL_FALSE, sizeof(TriangleVertex), // distance between two vertexColor 
		BUFFER_OFFSET(sizeof(float) * 3)	// note, the first color starts after the first vertex.
	);
}



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

	glewExperimental = GL_TRUE;
	GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		printf("ERROR: %s \n", glewGetErrorString(GlewInitResult));
		system("pause");
		exit(EXIT_FAILURE);

	}

	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	Shader shader("VS.glsl", "FS.glsl");

	shaderID = shader.getShaderID();

	CreateTriangleData();

	shader.enable();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Poll for and process events */
		glfwPollEvents();

		//Shader redShade("ProjectKiddo v.0.000002/vs.glsl", "ProjectKiddo v.0.000002/fs.glsl");

		glBindVertexArray(gVertexAttribute);

		/* Render here */
		game.draw(); //This is a basic openGL draw call - no shaders implemented
		

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}