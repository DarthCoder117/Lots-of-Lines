#include "LotsOfLines/DataModel.hpp"
#include "LotsOfLines/IDataLoader.hpp"

using namespace LotsOfLines;

DataModel::DataModel()
{}

DataModel::DataModel(const DataLoaderArray& dataLoaders)
	:m_dataLoaders(dataLoaders)
{}

void DataModel::registerLoader(IDataLoader* loader)
{
	m_dataLoaders.push_back(loader);
}

std::shared_ptr<DataSet> DataModel::loadData(const std::string& path) const
{
	DataLoaderArray::const_reverse_iterator iter;//Reverse iterator so that loaders registered later can override old ones.
	for (iter = m_dataLoaders.rbegin(); iter != m_dataLoaders.rend(); ++iter)
	{
		if ((*iter)->supportsFormat(path))
		{
			std::shared_ptr<DataSet> dataSet = (*iter)->loadData(path);
			if (dataSet != nullptr)
			{
				return dataSet;
			}
		}
	}

	return nullptr;
}