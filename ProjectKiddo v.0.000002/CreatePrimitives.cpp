#include "CreatePrimitives.h"



CreatePrimitive::CreatePrimitive()
{
	this->gVertexBuffer = 0;
	this->gVertexAttribute = 0;
	this->shaderID = 0;
}


CreatePrimitive::~CreatePrimitive()
{
}

void CreatePrimitive::CreateTriangleData()
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

void CreatePrimitive::setShaderID(GLuint shaderID)
{
	this->shaderID = shaderID;
}

GLuint CreatePrimitive::getshaderID() const
{
	return this->shaderID;
}

GLuint CreatePrimitive::getVertexAttribute() const
{
	return this->gVertexAttribute;
}

GLuint CreatePrimitive::getVertexBuffer() const
{
	return this->gVertexBuffer;
}
