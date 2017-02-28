#include "LotsOfLines/DataFileLoader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include "ben-strasser/csv.h"

using namespace LotsOfLines;

bool DataFileLoader::supportsFormat(const std::string& path)
{
	return path.find(".data") != path.npos;
}

std::shared_ptr<DataSet> DataFileLoader::loadData(const std::string& path, const LoadOptions& options) const
{
	io::LineReader in(path);
	std::shared_ptr<DataSet> dataSet = std::make_shared<DataSet>();

	// Skip first line for CSV format
	in.next_line();
	std::istringstream is;

	Vector vec;
	std::string dataClass, token;
	double xn;
	int column = 0, classC = 0;
	while (char *line = in.next_line()) {

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
	return dataSet;
}