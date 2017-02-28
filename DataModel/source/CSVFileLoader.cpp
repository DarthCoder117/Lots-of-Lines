#include "LotsOfLines/CSVFileLoader.hpp"
#include <fstream>
#include <regex>
#include <iostream>
#include <sstream>

using namespace LotsOfLines;

bool CSVFileLoader::supportsFormat(const std::string& path)
{
	return path.find(".csv") != path.npos;
}

std::shared_ptr<DataSet> CSVFileLoader::loadData(const std::string& path, const LoadOptions& options) const
{
	std::ifstream in(path);
	if (in)
	{
		std::shared_ptr<DataSet> dataSet = std::make_shared<DataSet>();

		// Skip first line for CSV format
		std::string line{ "" };
		std::istringstream is;

		Vector vec;
		std::string dataClass, token;
		double xn;
		int column = 0, classC = 0;
		while (in >> line) {
			if (line.empty()) continue;
			dataClass = "default";
			vec.clear();
			is.str(line);
			is.clear();
			while (std::getline(is, token, ',')) {
				try
				{
					xn = std::stod(token);
					vec.push_back(xn);
				}
				catch (std::invalid_argument e)
				{
					if (is.peek() != ',')
					{
						//If so, then this token is the data class label.
						dataClass = token;
					}
					else
					{
						//If not double, then attempt to convert to an appropriate numeric value
						std::string months[]{ "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };
						std::string days[]{ "sun", "mon", "tue", "wed", "thur", "fri", "sat" };

						//Try month or day conversion
						ptrdiff_t month_pos = std::find(std::begin(months), std::end(months), token) - std::begin(months);
						ptrdiff_t day_pos = std::find(std::begin(days), std::end(days), token) - std::begin(days);
						if (month_pos < sizeof(months) / sizeof(*months))
						{
							vec.push_back((double)month_pos);
						}
						else if (day_pos < sizeof(days) / sizeof(*days))
						{
							vec.push_back((double)day_pos);
						}
					}
				}
				catch (std::out_of_range e)
				{
					std::cout << e.what() << std::endl;
				}
				column++;
			}
			column = 0;
			dataSet->addVector(vec, dataClass);
		}
		in.close();
		return dataSet;
	}
	return nullptr;
}