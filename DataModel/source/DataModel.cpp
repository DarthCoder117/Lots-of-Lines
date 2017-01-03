#include "LotsOfLines/DataModel.h"

DataModel::DataModel()
{}

DataModel::DataModel(const DataLoaderArray& dataLoaders)
	:m_dataLoaders(dataLoaders)
{}

void DataModel::registerLoader(IDataLoader* loader) const
{

}