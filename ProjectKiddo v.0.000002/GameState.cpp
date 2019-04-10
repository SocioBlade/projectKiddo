#include "GameState.h"



GameState::GameState()
{
	this->triPos1 = glm::vec2(-0.5, -0.5);
	this->triPos2 = glm::vec2( 0.0,	 0.5);
	this->triPos3 = glm::vec2( 0.5, -0.5);
}


GameState::~GameState()
{
}

void GameState::draw()
{
	//Clear colour buffer before rendering
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	//Begin basic draw call for the triangle
	//glBegin(GL_TRIANGLES);

	//glVertex2f(triPos1.x, triPos1.y);
	//glVertex2f(triPos2.x, triPos2.y);
	//glVertex2f(triPos3.x, triPos3.y);

	//glEnd();
}
