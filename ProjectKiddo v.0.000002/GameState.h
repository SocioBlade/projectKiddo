#pragma once
#include "glew.h"
#include "glfw3.h"

#include "glm.hpp"
#include "ext.hpp"

#include <iostream>

class GameState
{
private:
	//Initial position values for the 2D triangle
	glm::vec2 triPos1,
			  triPos2,
			  triPos3;

public:
	GameState();
	~GameState();

	void draw();
};

