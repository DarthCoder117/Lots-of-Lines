#include <LoadingWorker.h>

LoadingWorker::LoadingWorker()
{

}

LoadingWorker::~LoadingWorker()
{

}

std::shared_ptr<LotsOfLines::DataSet> LoadingWorker::loadData(const QString& path, const LotsOfLines::LoadOptions& options)
{
	std::shared_ptr<LotsOfLines::DataSet> dataSet = m_dataModel.loadData(path.toStdString(), options);
	return dataSet;
}

void LoadingWorker::updateDataset(const QString& path, const LotsOfLines::LoadOptions& options)
{
	std::shared_ptr<LotsOfLines::DataSet> dataSet = loadData(path, options);
	emit datasetUpdated(dataSet);
}