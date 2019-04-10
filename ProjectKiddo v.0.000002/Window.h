#pragma once
#include "glew.h"
#include "glfw3.h"

#include "glm.hpp"
#include "ext.hpp"

#include <iostream>



class Window
{
private:
	int m_Width, m_Height;
	const char *m_Title;
	GLFWwindow *m_Window;

	bool _init();
public:
	Window(const char* name, int width, int height);
	~Window();
	void update();
	bool closed() const;
	void clear() const;

	int getWidth() const;
	int getHeight() const;
};