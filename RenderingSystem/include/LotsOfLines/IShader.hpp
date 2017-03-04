#ifndef I_SHADER_HPP
#define I_SHADER_HPP
#include <string>

namespace LotsOfLines
{
	class IShader
	{
	public:

		///@brief Compile a shader program from source code.
		virtual bool compile(const char* vertexShaderSrc, const char* fragmentShaderSrc) = 0;
	};
}

#endif