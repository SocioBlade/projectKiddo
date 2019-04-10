#include "shader.h"

engineTest::graphics::Shader::Shader(const char * vertPath, const char * fragPath)
	: m_VertPath(vertPath), m_FragPath(fragPath)
{
	m_ShaderID = _load();
}

engineTest::graphics::Shader::~Shader()
{
	glDeleteProgram(m_ShaderID);
}

void engineTest::graphics::Shader::setUniform1f(const GLchar * name, float value)
{
	glUniform1f(_getUniformLocation(name), value);
}

void engineTest::graphics::Shader::setUniform1i(const GLchar * name, int value)
{
	glUniform1i(_getUniformLocation(name), value);
}

void engineTest::graphics::Shader::setUniform2f(const GLchar * name, const glm::vec2 & vector)
{
	glUniform2f(_getUniformLocation(name), vector.x, vector.y);
}

void engineTest::graphics::Shader::setUniform3f(const GLchar * name, const glm::vec3 & vector)
{
	glUniform3f(_getUniformLocation(name), vector.x, vector.y, vector.z);
}

void engineTest::graphics::Shader::setUniform4f(const GLchar * name, const glm::vec4 & vector)
{
	glUniform4f(_getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}

void engineTest::graphics::Shader::setUniformMat4(const GLchar * name, const glm::mat4 & matrix)
{
	glUniformMatrix4fv(_getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

GLuint engineTest::graphics::Shader::getShaderID()
{
	return this->m_ShaderID;
}

void engineTest::graphics::Shader::enable() const
{
	glUseProgram(m_ShaderID);
}

void engineTest::graphics::Shader::disable() const
{
	glUseProgram(0);
}

GLuint engineTest::graphics::Shader::_load()
{
	GLuint program = glCreateProgram();
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertSourceString = FileUtils::read_file(m_VertPath);
	std::string fragSourceString = FileUtils::read_file(m_FragPath);

	const char* vertSource = vertSourceString.c_str();
	const char* fragSource = fragSourceString.c_str();

	glShaderSource(vertex, 1, &vertSource, NULL);
	glCompileShader(vertex);

	GLint result;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		GLint lenght;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &lenght);
		std::vector<char> error(lenght);
		glGetShaderInfoLog(vertex, lenght, &lenght, &error[0]);
		std::cout << "Failed to compile vertex shader! " << std::endl << &error[0] << std::endl;
		glDeleteShader(vertex);
		return 0;
	}

	glShaderSource(fragment, 1, &fragSource, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		GLint lenght;
		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &lenght);
		std::vector<char> error(lenght);
		glGetShaderInfoLog(fragment, lenght, &lenght, &error[0]);
		std::cout << "Failed to compile fragment shader! " << std::endl << &error[0] << std::endl;
		glDeleteShader(fragment);
		return 0;
	}

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return program;

}

GLint engineTest::graphics::Shader::_getUniformLocation(const GLchar * name)
{
	return glGetUniformLocation(m_ShaderID, name);
}
