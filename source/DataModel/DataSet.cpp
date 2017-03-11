#include "DataModel/DataSet.hpp"

using namespace LotsOfLines;

//===============================================================================
//DataSet
//===============================================================================
DataSet::DataSet()
{

}

unsigned int DataSet::addVectorClass(const std::string& vectorClass)
{
	auto iter = m_vectorClassIndices.find(vectorClass);
	if (iter == m_vectorClassIndices.end())
	{
		unsigned int idx = m_vectorClassIndices.size();
		m_vectorClassIndices[vectorClass] = idx;
		return idx;
	}

	return iter->second;

	/*
	m_dataClasses.insert(vectorClass);
	m_vectorData[vectorClass] = VectorClass();*/
}

unsigned int DataSet::getClassIndex(const std::string& name)
{
	auto iter = m_vectorClassIndices.find(name);
	return iter != m_vectorClassIndices.end() ? iter->second : 0;
}

void DataSet::addVector(const Vector& vec, const std::string& vectorClass)
{
	unsigned int classIdx = addVectorClass(vectorClass);

	VectorEntry entry;
	entry.data = vec;
	entry.dataClass = classIdx;
	m_vectorEntries.push_back(entry);

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
}

unsigned int DataSet::vectorCount() const
{
	return m_vectorEntries.size();
}

Vector& DataSet::getVector(unsigned int idx)
{
	return m_vectorEntries[idx].data;
}

const Vector& DataSet::getVector(unsigned int idx) const
{
	return m_vectorEntries[idx].data;
}

Vector& DataSet::operator [] (unsigned int idx)
{
	return getVector(idx);
}

const Vector& DataSet::operator [] (unsigned int idx) const
{
	return getVector(idx);
}

DataSet::Iterator DataSet::iterator() const
{
	return Iterator(this);
}

const static Vector EMPTY_VECTOR;

const Vector& DataSet::getMaxValues() const
{
	return m_maxValues;
}

const Vector& DataSet::getMinValues() const
{ 
	return  m_minValues;
}

void DataSet::normalizeData(E_DATA_NORMALIZATION_MODE mode)
{
	if (mode == EDNM_PER_VARIABLE)
	{
		//Use maximum values for each class and seperately for each variable
		const Vector& maxVals = getMaxValues();
		const Vector& minVals = getMinValues();

		for (VectorEntry& entry : m_vectorEntries)
		{
			for (unsigned int i = 0; i < entry.data.size(); ++i)
			{
				const double max = maxVals[i];
				const double min = minVals[i];
				const double x = entry.data[i];
				entry.data[i] = (2.0 * ((x - min) / (max - min))) - 1.0;
			}
		}
	}
	else if (mode == EDNM_GLOBAL_MIN_MAX)
	{
		//Collect min/max for each class
		double globalMax = 0.0;
		double globalMin = 0.0;
		
		const Vector& maxVals = getMaxValues();
		for (auto val : maxVals)
		{
			if (globalMax < val)
			{
				globalMax = val;
			}
		}
		const Vector& minVals = getMinValues();
		for (auto val : minVals)
		{
			if (globalMin > val)
			{
				globalMin = val;
			}
		}
		
		for (VectorEntry& entry : m_vectorEntries)
		{
			for (unsigned int i = 0; i < entry.data.size(); ++i)
			{
				const double max = globalMax;
				const double min = globalMin;
				const double x = entry.data[i];
				entry.data[i] = (2.0 * ((x - min) / (max - min))) - 1.0;
			}
		}
	}
}

//===============================================================================
//DataSet Iterator
//===============================================================================
DataSet::Iterator::Iterator(const DataSet* dataSet)
	:m_dataSet(dataSet),
	m_vectorIdx(0)
{

}

bool DataSet::Iterator::hasNext() const
{
	return m_vectorIdx < m_dataSet->m_vectorEntries.size();
}

DataSet::Iterator& DataSet::Iterator::operator ++ (int)
{
	m_vectorIdx++;
	return *this;
}

const Vector& DataSet::Iterator::vector()
{
	return m_dataSet->m_vectorEntries[m_vectorIdx].data;
}

unsigned int DataSet::Iterator::classIndex() const
{
	return m_dataSet->m_vectorEntries[m_vectorIdx].dataClass;
}

unsigned int DataSet::Iterator::lineIndex() const
{
	return m_vectorIdx;
}
