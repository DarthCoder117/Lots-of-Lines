#ifndef DATA_MODEL_H
#define DATA_MODEL_H
#include <vector>
#include <memory>
#include "IDataLoader.h"
#include "DataSet.h"

namespace LotsOfLines
{
	typedef std::vector<IDataLoader*> DataLoaderArray;

	///@brief The DataModel class handles loading and processing datasets to convert them to a form usable by the rendering system.
	class DataModel
	{
	public:

		DataModel();
		DataModel(const DataLoaderArray& dataLoaders);

		///@brief Register a data loader with the DataModel.
		///Data loaders implement the actual parsing logic.
		void registerLoader(IDataLoader* loader);

		///@brief Loads data from the specified source.
		///@param path The path to load data from. The format of this parameter is to be interpreted by the loader implementation
		///and could be a file path, a URL, or something else.
		///@return A shared_ptr to the DataSet loaded from the path, or nullptr if an error occurred.
		std::shared_ptr<DataSet> loadData(const std::string& path, const LoadOptions& options = LoadOptions::default) const;

	private:

		DataLoaderArray m_dataLoaders;
	};
}

#endif