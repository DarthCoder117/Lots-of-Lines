#include "LotsOfLines/DataSet.hpp"

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

	m_dataClasses.insert(vectorClass);
	m_vectorData[vectorClass].push_back(vec);
}