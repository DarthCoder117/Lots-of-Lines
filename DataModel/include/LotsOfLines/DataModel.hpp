#ifndef DATE_MODEL_H
#define DATA_MODEL_H
#include <vector>

namespace LotsOfLines
{
	class IDataLoader;

	typedef std::vector<IDataLoader> DataLoaderArray;

	///@brief The DataModel class handles loading and processing datasets to convert them to a form usable by the rendering system.
	class DataModel
	{
	public:

		DataModel();
		DataModel(const DataLoaderArray& dataLoaders);

		///@brief Register a data loader with the DataModel.
		///Data loaders implement the actual parsing logic.
		void registerLoader(IDataLoader* loader) const;

	private:

		DataLoaderArray m_dataLoaders;
	};
}

#endif