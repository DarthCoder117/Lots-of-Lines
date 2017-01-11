#ifndef I_RENDERER_H
#define I_RENDERER_H

namespace LotsOfLines
{
	class IRenderer
	{
	public:

		virtual ~IRenderer() {}

		virtual bool run() = 0;

		virtual void beginDraw(float r, float g, float b) = 0;

		virtual void endDraw() = 0;
	};
}

#endif