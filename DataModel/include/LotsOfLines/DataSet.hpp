#ifndef DATA_SET_H
#define DATA_SET_H
#include <vector>
#include <memory>

namespace LotsOfLines
{
	typedef std::vector<double> Vector;
	typedef std::vector<Vector> VectorClass;

	///@brief DataSet holds the data for multiple classes of vector data.
	class DataSet
	{
	public:

		///@brief Default constructor to make
		DataSet();
		///@brief Constructor for a dataset with one class of data and known capacity.
		///@param capacity Number of vectors in the dataset
		DataSet(unsigned int capacity);
		///@brief Constructor for a dataset with multiple classes of data and known capacity for each.
		///@param numClasses The number of data classes.
		///@param capacities Array with capacities for each data class.
		DataSet(unsigned int numClasses, unsigned int* capacities);

		///@brief Add a vector class to the dataset
		void addVectorClass();

		///@brief Get the collection of vectors for a class of data
		///@param vectorClass Data class number (class 0, 1, 2, etc.)
		const VectorClass& getVectors(unsigned int vectorClass);

		///@brief Add a vector to the specified class.
		///@param vectorClass Data class number (class 0, 1, 2, etc.)
		///@param vec The vector data to add.
		void addVector(unsigned int vectorClass, const Vector& vec);

	private:

		DataSet(const DataSet& oth) {} //Dissallow copy

		std::vector<VectorClass> m_vectorData;
	};

	typedef std::shared_ptr<DataSet> DataSetPtr;
}

#endif
