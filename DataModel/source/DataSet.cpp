#include "LotsOfLines/DataSet.hpp"

using namespace LotsOfLines;

DataSet::DataSet()
{

}

void DataSet::addVectorClass(const std::string& vectorClass)
{
	m_vectorData[vectorClass] = VectorClass();
}

const VectorClass& DataSet::getVectors(const std::string& vectorClass)
{
	return m_vectorData[vectorClass];
}

void DataSet::addVector(const Vector& vec, const std::string& vectorClass)
{
	m_vectorData[vectorClass].push_back(vec);
}