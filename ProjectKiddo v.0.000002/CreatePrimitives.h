#pragma once
#include "glew.h"
#include "glfw3.h"

#include "glm.hpp"
#include "ext.hpp"
#include <iostream>

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

class CreatePrimitive
{
private:
	GLuint gVertexBuffer;
	GLuint gVertexAttribute;
	GLuint shaderID;

public:
	CreatePrimitive();
	~CreatePrimitive();

	void CreateTriangleData();

	void setShaderID(GLuint shaderID);

	GLuint getshaderID() const;
	GLuint getVertexAttribute() const;
	GLuint getVertexBuffer() const;
};

