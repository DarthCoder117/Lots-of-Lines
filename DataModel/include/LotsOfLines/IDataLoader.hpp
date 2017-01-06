#ifndef I_DATA_LOADER_H
#define I_DATA_LOADER_H
#include "LotsOfLines/DataSet.hpp"
#include <string>

namespace LotsOfLines
{
	class IDataLoader
	{
	public:

		virtual ~IDataLoader() {}

		///@param path The path (file path, URI, etc.) where the data will be loaded from.
		///@return True if this loader supports loading the specified path, false otherwise.
		virtual bool supportsFormat(const std::string& path) = 0;

		///@brief Load vector data from a source specified by the path and output it as an array of vectors.
		///@param path The path (file path, URI, etc.) where the data should be loaded from. 
		///@return The DataSet or nullptr if an error occurred.
		virtual DataSetPtr loadData(const std::string& path) const = 0;
	};
}

#endif