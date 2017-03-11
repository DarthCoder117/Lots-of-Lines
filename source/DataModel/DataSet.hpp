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
		EDNM_PER_VARIABLE,///< Use min and max for each variable.
		EDNM_GLOBAL_MIN_MAX,///< Use global min and max for whole data set.
	};

	///@brief DataSet holds the data for multiple classes of vector data
	class DataSet
	{
	public:

		///@brief Iterator class for traversing the dataset easier.
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

			///@return The index of the current vector.
			unsigned int lineIndex() const;

		protected:

			friend class DataSet;
			Iterator(const DataSet* dataSet);

			const DataSet* m_dataSet;

			unsigned int m_vectorIdx;
		};

		///@return An iterator that can be used to traverse this dataset.
		Iterator iterator() const;

		///@return The number of vectors in the dataset
		unsigned int vectorCount() const;
		///@return The vector at the specified index.
		Vector& getVector(unsigned int idx);
		///@return The vector at the specified index.
		const Vector& getVector(unsigned int idx) const;
		///@brief subscript operator for accessing vectors at the specified index.
		Vector& operator [] (unsigned int idx);
		///@brief subscript operator for accessing vectors at the specified index.
		const Vector& operator [] (unsigned int idx) const;

		///@brief Default constructor to make
		DataSet();
		
		///@brief Add a vector class to the dataset
		///@return The index of the vector class that was added.
		unsigned int addVectorClass(const std::string& name);
		///@brief Get class index from the class name.
		unsigned int getClassIndex(const std::string& name);

		///@brief Add a vector to the specified class.
		///@param vectorClass Data class name.
		///@param vec The vector data to add.
		void addVector(const Vector& vec, const std::string& vectorClass = "default");

		const Vector& getMaxValues() const;
		const Vector& getMinValues() const;

		///@brief Normalize the vector data to the -1.0 to 1.0 range.
		///This should only be called once all vectors have been loaded to the dataset.
		void normalizeData(E_DATA_NORMALIZATION_MODE mode);

	private:
		
		std::map<std::string, unsigned int> m_vectorClassIndices;

		struct VectorEntry
		{
			Vector data;
			unsigned int dataClass;
		};

		std::vector<VectorEntry> m_vectorEntries;

                //DataSet(const DataSet& oth) {} //Dissallow copy

		Vector m_maxValues;
		Vector m_minValues;
	};
}

#endif
