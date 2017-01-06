#ifndef I_DATA_LOADER_H
#define I_DATA_LOADER_H
#include <iostream>

namespace LotsOfLines
{
	class IDataLoader
	{
	public:

		virtual ~IDataLoader() {}

		///@brief Load vector data from the input stream and output it as an array of vectors.
		///@return True if the data was loaded correctly, false if there was an error, or the format was unsupported by this loader.
		virtual bool loadData(const std::istream& in) const = 0;
	};
}

#endif