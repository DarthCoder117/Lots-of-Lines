#ifndef PROGRESS_MESSAGE_H
#define PROGRESS_MESSAGE_H

namespace LotsOfLines
{
	class ProgressMessage
	{
	public:
		virtual void progress(int p) = 0;
	};
}

#endif // !PROGRESS_MESSAGE_H
