#include "Window.h"

//#####################################//
// _init function sets everything up   //
// for the creation of a glfw window   //
// and initializes glew.               //
//#####################################//
bool Window::_init()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return false;
	}
	m_Window = glfwCreateWindow(m_Height, m_Width, m_Title, NULL, NULL);
	if (!m_Window)
	{
		std::cout << "Failed to create glfw window" << std::endl;
		return false;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(m_Window);

	glfwSetWindowUserPointer(m_Window, this);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glewExperimental = GL_TRUE;
	GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		printf("ERROR: %s \n", glewGetErrorString(GlewInitResult));
		system("pause");
		exit(EXIT_FAILURE);

	}
	return true;
}

//#####################################//
// Window constructor that sets values  //
// for title, height and width.        //
//#####################################//
Window::Window(const char *title, int height, int width)
{
	this->m_Title = title;
	this->m_Height = height;
	this->m_Width = width;

	if (!_init())
	{
		glfwTerminate();
	}
}

Window::~Window()
{
	glfwTerminate();
}

//#####################################//
// Update function that handles glfw's //
// poll and swap buffers.              //
//#####################################//
void Window::update()
{
	/* Poll for and process events */
	glfwPollEvents();
	/* Swap front and back buffers */
	glfwSwapBuffers(m_Window);
}

//#####################################//
// Function checks if the window is    //
// closed.                             //
//#####################################//
bool Window::closed() const
{
	return glfwWindowShouldClose(m_Window) == 1;
}

//#####################################//
// Simple function that handles        //
// clearing of screen                  //
//#####################################//
void Window::clear() const
{
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//#####################################//
// Getter that returns the width of    //
// the window.	                       //
//#####################################//
int Window::getWidth() const
{
	return m_Width;
}

//#####################################//
// Getter that returns the height of   //
// the window.                         //
//#####################################//
int Window::getHeight() const
{
	return m_Height;
}