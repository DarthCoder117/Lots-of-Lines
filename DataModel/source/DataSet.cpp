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
		for (auto dataClass : m_dataClasses)
		{
			//Use maximum values for each class and seperately for each variable
			const Vector& maxVals = getMaxValues();
			const Vector& minVals = getMinValues();

			VectorClass& vectors = m_vectorData[dataClass];
			for (Vector& vector : vectors)
			{
				for (unsigned int i = 0; i < vector.size(); ++i)
				{
					const double max = maxVals[i];
					const double min = minVals[i];
					const double x = vector[i];
					vector[i] = (2.0 * ((x - min) / (max - min))) - 1.0;
				}
			}
		}
	}
	else if (mode == EDNM_GLOBAL_MIN_MAX)
	{
		//Collect min/max for each class
		double globalMax = 0.0;
		double globalMin = 0.0;
		for (auto dataClass : m_dataClasses)
		{
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
		}

		for (auto dataClass : m_dataClasses)
		{
			VectorClass& vectors = m_vectorData[dataClass];
			for (Vector& vector : vectors)
			{
				for (unsigned int i = 0; i < vector.size(); ++i)
				{
					const double max = globalMax;
					const double min = globalMin;
					const double x = vector[i];
					vector[i] = (2.0 * ((x - min) / (max - min))) - 1.0;
				}
			}
		}
	}
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

	//Get current vector class
	m_currentVectorClass = &m_dataSet->getVectors(m_classNames[m_classIdx]);
}

bool DataSet::Iterator::hasNext() const
{
	return m_classIdx < m_classNames.size();
}

DataSet::Iterator& DataSet::Iterator::operator ++ (int)
{
	m_vectorIdx++;

	//If the end of the current vector class is reached, then update the current vector class.
	if (m_currentVectorClass && m_vectorIdx >= m_currentVectorClass->size())
	{
		m_vectorIdx = 0;
		m_classIdx++;

		//Update pointer to current vector class to avoid more name lookups
		if (m_classIdx < m_classNames.size())
		{
			m_currentVectorClass = &m_dataSet->getVectors(m_classNames[m_classIdx]);
		}
	}

	return *this;
}

const Vector& DataSet::Iterator::vector()
{
	return (*m_currentVectorClass)[m_vectorIdx];
}

unsigned int DataSet::Iterator::classIndex() const
{
	return m_classIdx;
}

const std::string& DataSet::Iterator::className() const
{
	return m_classNames[m_classIdx];
}
