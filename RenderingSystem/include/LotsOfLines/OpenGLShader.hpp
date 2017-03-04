#ifndef OPENGL_SHADER_HPP
#define OPENGL_SHADER_HPP
#include "LotsOfLines/IShader.hpp"

namespace LotsOfLines
{
	class OpenGLShader : public IShader
	{
	public:

		///@brief Compile a shader program from source code.
		bool compile(const char* vertexShaderSrc, const char* fragmentShaderSrc);

		///@return The compiled GLSL program.
		unsigned int getProgram() const;

	private:

		unsigned int m_program = 0;
	};
}

#endif
