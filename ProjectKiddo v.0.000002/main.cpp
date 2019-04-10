#include <iostream>
#include <windows.h>

#include "glew.h"
#include "glfw3.h"

#include "glm.hpp"
#include "ext.hpp"

#include "GameState.h"
#include "Window.h"
#include "CreatePrimitives.h"

#include "shader.h"

using namespace engineTest;
using namespace graphics;

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

int main(void)
{
	Window m_Window("Project Kiddo", 640, 480);
	GameState game;
	CreatePrimitive shape;

	/* Make the window's context current */

	glewExperimental = GL_TRUE;
	
	m_Window.clear();

	Shader shader("VS.glsl", "FS.glsl");
	shape.setShaderID(shader.getShaderID());
	shape.CreateTriangleData();
	shader.enable();

	/* Loop until the user closes the window */
	while (!m_Window.closed())
	{
		m_Window.update();
		glBindVertexArray(shape.getVertexAttribute());
		/* Render here */
		game.draw();
	}
	return 0;
}