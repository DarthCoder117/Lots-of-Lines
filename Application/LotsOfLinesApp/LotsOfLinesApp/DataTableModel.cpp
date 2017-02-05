#include "DataTableModel.h"

DataTableModel::DataTableModel(std::shared_ptr<LotsOfLines::DataSet> dataSet, const std::string& dataClass)
	:m_dataSet(dataSet),
	m_dataClass(dataClass)
{

}

int DataTableModel::rowCount(const QModelIndex& parent) const
{
	return m_dataSet->getVectors(m_dataClass).size();
}

int DataTableModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant DataTableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int col = index.column();

	if (role == Qt::DisplayRole)
	{
		const LotsOfLines::Vector& vec = m_dataSet->getVectors(m_dataClass)[row];
		return vec[col];
	}
	
	return QVariant::Invalid;
}

/*QVariant DataTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{

}*/
