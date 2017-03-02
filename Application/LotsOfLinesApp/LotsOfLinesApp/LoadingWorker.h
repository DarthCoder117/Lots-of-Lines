#pragma once

#include <QtWidgets>
#include "LotsOfLines/DataModel.hpp"
#include "LotsOfLines/DataSet.hpp"

class LoadingWorker : public QObject
{
	Q_OBJECT

public:
	LoadingWorker();
	~LoadingWorker();
	std::shared_ptr<LotsOfLines::DataSet> loadData(const QString& path, const LotsOfLines::LoadOptions& options);

public slots:
	void updateDataset(const QString& path, const LotsOfLines::LoadOptions& options);

signals:
	void datasetUpdated(std::shared_ptr<LotsOfLines::DataSet>);

private:
	void run()
	{
		// Empty
	}

protected:
	LotsOfLines::DataModel m_dataModel;
};