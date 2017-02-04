#include "LotsOfLines/DataSet.hpp"

using namespace LotsOfLines;

//===============================================================================
//DataSet
//===============================================================================
DataSet::DataSet()
{

}

void DataSet::addVectorClass(const std::string& vectorClass)
{
	m_dataClasses.insert(vectorClass);
	m_vectorData[vectorClass] = VectorClass();
}

const std::set<std::string>& DataSet::getClasses() const
{
	return m_dataClasses;
}

const VectorClass& DataSet::getVectors(const std::string& vectorClass) const
{
	static const VectorClass emptyClass;

	auto iter = m_vectorData.find(vectorClass);
	if (iter != m_vectorData.end())	return iter->second;

	return emptyClass;
}

void DataSet::addVector(const Vector& vec, const std::string& vectorClass)
{
	if (vectorClass.empty()) return;

	if (m_maxValues.empty())
	{
		m_maxValues.resize(vec.size(), -INFINITY);
		m_minValues.resize(vec.size(), INFINITY);
	}

	for (unsigned int i = 0; i < vec.size(); ++i)
	{
		if (m_maxValues[i] < vec[i]) m_maxValues[i] = vec[i];
		if (m_minValues[i] > vec[i]) m_minValues[i] = vec[i];
	}

	m_dataClasses.insert(vectorClass);
	m_vectorData[vectorClass].push_back(vec);
}

unsigned int DataSet::vectorCount() const
{
	unsigned int count = 0;

	for (auto dataClass : m_dataClasses)
	{
		count += getVectors(dataClass).size();
	}

	return count;
}

DataSet::Iterator DataSet::iterator() const
{
	return Iterator(this);
}

//===============================================================================
//DataSet Iterator
//===============================================================================
DataSet::Iterator::Iterator(const DataSet* dataSet)
	:m_dataSet(dataSet),
	m_classIdx(0),
	m_vectorIdx(0)
{
	//Get class index array
	for (auto iter : m_dataSet->getClasses())
	{
		m_classNames.push_back(iter);
	}
}

bool DataSet::Iterator::hasNext() const
{
	return m_classIdx < m_classNames.size();
}

DataSet::Iterator& DataSet::Iterator::operator ++ (int)
{
	auto currentClass = m_dataSet->getVectors(m_classNames[m_classIdx]);

	m_vectorIdx++;
	if (m_vectorIdx >= currentClass.size())
	{
		m_vectorIdx = 0;
		m_classIdx++;
	}

	return *this;
}

const Vector* DataSet::Iterator::vector()
{
	return &m_dataSet->getVectors(m_classNames[m_classIdx])[m_vectorIdx];
}

unsigned int DataSet::Iterator::classIndex() const
{
	return m_classIdx;
}

const std::string& DataSet::Iterator::className() const
{
	return m_classNames[m_classIdx];
}
