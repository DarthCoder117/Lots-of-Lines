#ifndef DATA_SET_H
#define DATA_SET_H
#include <map>
#include <set>
#include <vector>

namespace LotsOfLines
{
	typedef std::vector<double> Vector;
	typedef std::vector<Vector> VectorClass;

	///@brief DataSet holds the data for multiple classes of vector data
	class DataSet
	{
	public:

		///@brief Iterator class for traversing the datset easier.
		class Iterator
		{
		public:

			Iterator& operator ++ (int);

			///@return True if there's a next vector available, false if the end has been reached.
			bool hasNext() const;

			///@return Vector in the DataSet, or nullptr if the end has been reached.
			const Vector* vector();

			///@return The class index of the current vector.
			unsigned int classIndex() const;
			///@return The name of the vector class.
			const std::string& className() const;

		protected:

			friend class DataSet;
			Iterator(const DataSet* dataSet);

			const DataSet* m_dataSet;
			std::vector<std::string> m_classNames;

			unsigned int m_classIdx, m_vectorIdx;
		};

		///@return An iterator that can be used to traverse this dataset.
		Iterator iterator() const;

		///@return The number of vectors in the dataset
		unsigned int vectorCount() const;

		///@brief Default constructor to make
		DataSet();
		
		///@brief Add a vector class to the dataset
		void addVectorClass(const std::string& name);

		///@return The set of vector classes contained in this DataSet.
		const std::set<std::string>& getClasses() const;

		///@brief Get the collection of vectors for a class of data
		///@param vectorClass Data class name.
		const VectorClass& getVectors(const std::string& vectorClass) const;

		///@brief Add a vector to the specified class.
		///@param vectorClass Data class name.
		///@param vec The vector data to add.
		void addVector(const Vector& vec, const std::string& vectorClass = "default");

		const Vector& getMaxValues() const { return m_maxValues; }
		const Vector& getMinValues() const { return m_minValues; }

	private:

		DataSet(const DataSet& oth) {} //Dissallow copy

		std::set<std::string> m_dataClasses;
		std::map<std::string, VectorClass> m_vectorData;

		Vector m_maxValues;
		Vector m_minValues;
	};
}

#endif
