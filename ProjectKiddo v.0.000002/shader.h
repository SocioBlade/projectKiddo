#pragma once
#include <vector>
#include <iostream>
#include <glew.h>

#include "glm.hpp"
#include "ext.hpp"

#include "fileutils.h"


namespace engineTest {
	namespace graphics {

		class Shader
		{
		private:
			GLuint m_ShaderID;
			const char *m_VertPath;
			const char *m_FragPath;

			GLuint _load();
			GLint _getUniformLocation(const GLchar* name);
		public:
			Shader(const char* vertPath, const char* fragPath);
			~Shader();


			void setUniform1f(const GLchar* name, float value);
			void setUniform1i(const GLchar* name, int value);
			void setUniform2f(const GLchar* name, const glm::vec2& vector);
			void setUniform3f(const GLchar* name, const glm::vec3& vector);
			void setUniform4f(const GLchar* name, const glm::vec4& vector);
			void setUniformMat4(const GLchar* name, const glm::mat4& matrix);



			void enable() const;
			void disable() const;

		};

	}
}