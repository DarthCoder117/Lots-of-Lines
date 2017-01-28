#ifndef DATA_FILE_LOADER_H
#define DATA_FILE_LOADER_H
#include "IDataLoader.h"
#include <string>

namespace LotsOfLines
{
	class DataFileLoader : public IDataLoader
	{
	public:

		bool supportsFormat(const std::string& path);

		std::shared_ptr<DataSet> loadData(const std::string& path, const LoadOptions& options) const;
	};
}

#endif
