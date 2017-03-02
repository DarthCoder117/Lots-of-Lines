#include <LoadingWorker.h>
#include "LotsOfLines\ProgressMessage.hpp"

LoadingWorker::LoadingWorker(LotsOfLines::ProgressMessage* progress) : m_progress(progress) {}

std::shared_ptr<LotsOfLines::DataSet> LoadingWorker::loadData(const QString& path, const LotsOfLines::LoadOptions& options)
{
	std::shared_ptr<LotsOfLines::DataSet> dataSet = m_dataModel.loadData(path.toStdString(), options, m_progress);
	return dataSet;
}

void LoadingWorker::updateDataset(const QString& path, const LotsOfLines::LoadOptions& options)
{
	std::shared_ptr<LotsOfLines::DataSet> dataSet = loadData(path, options);
	emit datasetUpdated(dataSet);
}