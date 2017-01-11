#ifndef FILE_SYSTEM_LOADER_H
#define FILE_SYSTEM_LOADER_H
#include "LotsOfLines/IDataLoader.hpp"
#include <string>

namespace LotsOfLines
{
	class DataFileLoader : public IDataLoader
	{
	public:

		bool supportsFormat(const std::string& path);

		std::shared_ptr<DataSet> loadData(const std::string& path) const;
	};
}

#endif
