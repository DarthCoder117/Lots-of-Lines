#ifndef DATA_SET_H
#define DATA_SET_H
#include <map>
#include <vector>

namespace LotsOfLines
{
	typedef std::vector<double> Vector;
	typedef std::vector<Vector> VectorClass;

	///@brief DataSet holds the data for multiple classes of vector data
	class DataSet
{
	public:

		///@brief Default constructor to make
		DataSet();
		
		///@brief Add a vector class to the dataset
		void addVectorClass(const std::string& name);

		///@brief Get the collection of vectors for a class of data
		///@param vectorClass Data class name.
		const VectorClass& getVectors(const std::string& vectorClass);

		///@brief Add a vector to the specified class.
		///@param vectorClass Data class name.
		///@param vec The vector data to add.
		void addVector(const Vector& vec, const std::string& vectorClass = "default");

	private:

		DataSet(const DataSet& oth) {} //Dissallow copy

		std::map<std::string, VectorClass> m_vectorData;
	};
}

#endif
