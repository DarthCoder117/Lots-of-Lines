#include "LotsOfLines/Shaders.hpp"

using namespace LotsOfLines;

//==================================================================================
// Default visualization
//==================================================================================
const char* defaultVisualizationVertex = 
"#version 330 core\n"

"const uint SELECTED = 0x01u;\n"
"const uint HIDDEN = 0x02u;\n"

"uniform mat4 MVP;\n"
"uniform vec3 dataClassColors[10];\n"

"layout(location = 0) in vec3 pos;\n"
"layout(location = 1) in uint classIndex;\n"
"layout(location = 2) in uint flags;\n"

"out vec3 fragmentColor;\n"
"flat out uint fragmentFlags;\n"
"void main()\n"
"{\n"
"   gl_Position = MVP * vec4(pos, 1.0);\n"
"	fragmentColor = dataClassColors[classIndex];\n"
"   fragmentFlags = flags;\n"
"}\n";

const char* defaultVisualizationFragment =
"#version 330 core\n"

"const uint SELECTED = 0x01u;\n"
"const uint HIDDEN = 0x02u;\n"

"in vec3 fragmentColor;\n"
"flat in uint fragmentFlags;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"	if ((fragmentFlags & SELECTED) != 0u) discard;\n"
"   color = fragmentColor;\n"
"}\n";

//==================================================================================
// Selected line
//==================================================================================

const char* selectedLineFragment =
"#version 330 core\n"

"const uint SELECTED = 0x01u;\n"
"const uint HIDDEN = 0x02u;\n"

"in vec3 fragmentColor;\n"
"flat in uint fragmentFlags;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"	if ((fragmentFlags & SELECTED) == 0u) discard;\n"
"   color = vec3(1.0);\n"
"}\n";

//==================================================================================
// Point
//==================================================================================
const char* pointVertex =
"#version 330 core\n"

"const uint SELECTED = 0x01u;\n"
"const uint HIDDEN = 0x02u;\n"
"const uint DRAW_POINT = 0x04u;\n"

"uniform mat4 MVP;\n"
"uniform vec3 dataClassColors[10];\n"

"layout(location = 0) in vec3 pos;\n"
"layout(location = 1) in uint classIndex;\n"
"layout(location = 2) in uint flags;\n"

"out vec3 fragmentColor;\n"
"void main()\n"
"{\n"
"   gl_Position = MVP * vec4(pos, 1.0);\n"

"	float pointSz = 1.0;"
"	fragmentColor = dataClassColors[classIndex];\n"

"	if ((flags & SELECTED) != 0u)\n"
"	{\n"
"		pointSz = 4.0;\n"
"		fragmentColor = vec3(1.0);\n"
"	}\n"
"	if ((flags & DRAW_POINT) != 0u)\n"
"	{\n"
"		pointSz = 6.0;\n"
"	}\n"

"	gl_PointSize = pointSz;\n"
"}\n";

const char* pointFragment =
"#version 330 core\n"

"in vec3 fragmentColor;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"   color = fragmentColor;\n"
"}\n";

IShader* Shaders::defaultVisualization = nullptr;
IShader* Shaders::selectedLine = nullptr;
IShader* Shaders::point = nullptr;

bool Shaders::compileShaders(IRenderer* driver)
{
	defaultVisualization = driver->createShader();
	if (!defaultVisualization->compile(defaultVisualizationVertex, defaultVisualizationFragment)) return false;

	selectedLine = driver->createShader();
	if (!selectedLine->compile(defaultVisualizationVertex, selectedLineFragment)) return false;

	point = driver->createShader();
	if (!point->compile(pointVertex, pointFragment)) return false;

	return true;
}