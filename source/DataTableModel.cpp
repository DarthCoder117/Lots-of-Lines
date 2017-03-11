#include "DataTableModel.h"

DataTableModel::DataTableModel(std::shared_ptr<LotsOfLines::DataSet> dataSet)
	:m_dataSet(dataSet)
{

}

int DataTableModel::rowCount(const QModelIndex&) const
{
	return m_dataSet->vectorCount();
}

int DataTableModel::columnCount(const QModelIndex&) const
{
	return m_dataSet->getVector(0).size();
}

QVariant DataTableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int col = index.column();

	if (role == Qt::DisplayRole)
	{
		const LotsOfLines::Vector& vec = m_dataSet->getVector(row);
		return vec[col];
	}
	
	return QVariant::Invalid;
}

/*QVariant DataTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{

}*/
