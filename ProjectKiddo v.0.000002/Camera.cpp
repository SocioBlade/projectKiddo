#include "Camera.h"

void Camera::reCalcCamVecs()
{
	{
		glm::vec3 face;
		face.x = cos(glm::radians(this->camYaw)) * cos(glm::radians(this->camPitch));
		face.y = sin(glm::radians(this->camPitch));
		face.z = sin(glm::radians(this->camYaw)) * cos(glm::radians(this->camPitch));

		this->face = glm::normalize(face);

		this->camRight = glm::normalize(glm::cross(this->face, this->worldUp));
		this->camUp = glm::normalize(glm::cross(this->camRight, this->face));
	}
}

Camera::Camera(glm::vec3 pos = glm::vec3(0, 0, 0), glm::vec3 up = glm::vec3(0, 1, 0), float camYaw = -90.0f, float camPitch = 0.0f)
	: face(glm::vec3(0, 0, -1)), mSpeed(3.5f), sensitivity(0.15)//, zoom(40.0f)
{
	this->camPos = pos;
	this->worldUp = up;
	this->camYaw = camYaw;
	this->camPitch = camPitch;

	reCalcCamVecs();
}

void Camera::FPSCamControls(GLFWwindow * window, float deltaTime)
{
	float camSpeed = this->mSpeed*deltaTime;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		this->camPos -= camSpeed * this->camRight;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		this->camPos += camSpeed * this->camRight;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		this->camPos += camSpeed*this->face;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		this->camPos -= camSpeed * this->face;
}

glm::mat4 Camera::GetViewMatrix()
{
	//Calculates the view matrix given the camera positions.
	return glm::lookAt(this->camPos, this->camPos + this->face, this->camUp);
}

void Camera::pitchYawMouse(float xOffset, float yOffset, bool limitPitch = true)
{
	xOffset *= this->sensitivity;
	yOffset *= this->sensitivity;

	if (limitPitch)
	{
		if (this->camPitch > 89.0f)
			this->camPitch = 89.0f;
		if (this->camPitch < -89.0f)
			this->camPitch = 89.0f;
	}

	reCalcCamVecs();
}
