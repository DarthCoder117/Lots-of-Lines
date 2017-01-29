#ifndef CSV_FILE_SYSTEM_LOADER_H
#define CSV_FILE_SYSTEM_LOADER_H
#include "IDataLoader.h"
#include <string>

namespace LotsOfLines
{
	class CSVFileLoader : public IDataLoader
	{
	public:

		bool supportsFormat(const std::string& path);

		std::shared_ptr<DataSet> loadData(const std::string& path, const LoadOptions& options) const;
	};
}

#endif
