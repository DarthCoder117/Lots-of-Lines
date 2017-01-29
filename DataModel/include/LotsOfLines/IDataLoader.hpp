#ifndef I_DATA_LOADER_H
#define I_DATA_LOADER_H
#include "LotsOfLines/DataSet.hpp"
#include <string>
#include <memory>

namespace LotsOfLines
{
	struct LoadOptions
	{
		LoadOptions()
			:classColumn(0)
		{}

		static const LoadOptions default;

		///@brief Column to use as data class label
		unsigned int classColumn;
		///@brief Array of columns to ignore when loading the data.
		std::vector<unsigned int> ignoreColumns;
	};

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
		virtual std::shared_ptr<DataSet> loadData(const std::string& path, const LoadOptions& options) const = 0;
	};
}

#endif