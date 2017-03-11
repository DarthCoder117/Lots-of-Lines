#ifndef DATA_TABLE_MODEL_H
#define DATA_TABLE_MODEL_H
#include <DataModel/DataSet.hpp>
#include <memory>
#include <QAbstractTableModel>

///@brief Qt table model for showing one vector class of a DataSet
class DataTableModel : public QAbstractTableModel
{
public:

	DataTableModel(std::shared_ptr<LotsOfLines::DataSet> dataSet);

    int rowCount(const QModelIndex&) const;

    int columnCount(const QModelIndex&) const;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

	//QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:

	std::shared_ptr<LotsOfLines::DataSet> m_dataSet;
};

#endif
