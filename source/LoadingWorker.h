#pragma once

#include <QtWidgets>
#include "DataModel/DataModel.hpp"
#include "DataModel/DataSet.hpp"
#include "DataModel/ProgressMessage.hpp"

class LoadingWorker : public QObject
{
	Q_OBJECT

public:
	LoadingWorker(LotsOfLines::ProgressMessage*);
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
	LotsOfLines::ProgressMessage *m_progress;
};
