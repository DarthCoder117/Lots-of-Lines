#include "DataSet.h"

using namespace LotsOfLines;

DataSet::DataSet()
{

}

void DataSet::addVectorClass(const std::string& vectorClass)
{
	m_dataClasses.insert(vectorClass);
	m_vectorData[vectorClass] = VectorClass();
}

const std::set<std::string>& DataSet::getClasses()
{
	return m_dataClasses;
}

const VectorClass& DataSet::getVectors(const std::string& vectorClass)
{
	return m_vectorData[vectorClass];
}

void DataSet::addVector(const Vector& vec, const std::string& vectorClass)
{
	if (vectorClass.empty()) return;

	if (m_maxValues.empty())
	{
		m_maxValues.resize(vec.size());
		m_minValues.resize(vec.size());
	}

	for (unsigned int i = 0; i < vec.size(); ++i)
	{
		if (m_maxValues[i] < vec[i]) m_maxValues[i] = vec[i];
		if (m_minValues[i] > vec[i]) m_minValues[i] = vec[i];
	}

	m_dataClasses.insert(vectorClass);
	m_vectorData[vectorClass].push_back(vec);
}