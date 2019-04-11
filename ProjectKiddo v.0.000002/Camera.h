#pragma once

#include <iostream>

#include "glew.h"
#include "glfw3.h"

#include "glm.hpp"
#include "ext.hpp"



class Camera
{
private:

	void reCalcCamVecs();

public:
	glm::vec3 camPos;
	glm::vec3 face;
	glm::vec3 worldUp;
	glm::vec3 camUp;
	glm::vec3 camRight;

	float camYaw;
	float camPitch;

	//Should only apply to some cameras.
	float mSpeed;
	//float zoom;
	float sensitivity;

	//The Camera Constructor
	Camera(glm::vec3 pos, glm::vec3 up, float camYaw, float camPitch);

	//WASD camera movement controls. Need only be called in gameLoop if you want to move the specific camera.
	//Add custom key bindings for devs? Could send in letters as strings and use those as keybinds.
	void FPSCamControls(GLFWwindow * window, float deltaTime);

	//Calculates and returns the view matrix.
	glm::mat4 GetViewMatrix();

	//Pitch and yaw dependent on mouse movement if active. If limitPitch true standard FPS cam, No Flipping.
	void pitchYawMouse(float xOffset, float yOffset, bool limitPitch);






};
