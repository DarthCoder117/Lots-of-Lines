#include "LotsOfLines/DataModel.hpp"
#include "LotsOfLines/IDataLoader.hpp"

#include "LotsOfLines/DataFileLoader.hpp"
#include "LotsOfLines/CSVFileLoader.hpp"

using namespace LotsOfLines;

const LoadOptions LoadOptions::default = LoadOptions();

DataModel::DataModel()
{
	registerLoader(new DataFileLoader());
	registerLoader(new CSVFileLoader());
}

DataModel::DataModel(const DataLoaderArray& dataLoaders)
	:m_dataLoaders(dataLoaders)
{}

void DataModel::registerLoader(IDataLoader* loader)
{
	m_dataLoaders.push_back(loader);
}

std::shared_ptr<DataSet> DataModel::loadData(const std::string& path, const LoadOptions& options) const
{
	DataLoaderArray::const_reverse_iterator iter;//Reverse iterator so that loaders registered later can override old ones.
	for (iter = m_dataLoaders.rbegin(); iter != m_dataLoaders.rend(); ++iter)
	{
		if ((*iter)->supportsFormat(path))
		{
			std::shared_ptr<DataSet> dataSet = (*iter)->loadData(path, options);
			if (dataSet != nullptr)
			{
				dataSet->normalizeData(options.dataNormalizationMode);
				return dataSet;
			}
		}
	}

	return nullptr;
}