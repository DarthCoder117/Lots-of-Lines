#ifndef DATA_SET_H
#define DATA_SET_H
#include <map>
#include <set>
#include <vector>

namespace LotsOfLines
{
	typedef std::vector<double> Vector;
	typedef std::vector<Vector> VectorClass;

	enum E_DATA_NORMALIZATION_MODE
	{
		EDNM_NONE,
		EDNM_PER_VARIABLE,///< Use min and max for each variable in each data class.
		EDNM_GLOBAL_MIN_MAX,///< Use global min and max for whole data set.
		EDNM_PER_CLASS,///< Use global min and max for whole data class.
	};

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
			const Vector& vector();

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
			const std::vector<Vector>* m_currentVectorClass;
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

		const Vector& getMaxValues(const std::string& vectorClass = "default") const;
		const Vector& getMinValues(const std::string& vectorClass = "default") const;

		///@brief Normalize the vector data to the -1.0 to 1.0 range.
		///This should only be called once all vectors have been loaded to the dataset.
		void normalizeData(E_DATA_NORMALIZATION_MODE mode);

	private:

		DataSet(const DataSet& oth) {} //Dissallow copy

		std::set<std::string> m_dataClasses;
		std::map<std::string, VectorClass> m_vectorData;

		std::map<std::string, Vector> m_maxValues;
		std::map<std::string, Vector> m_minValues;
	};
}

#endif
