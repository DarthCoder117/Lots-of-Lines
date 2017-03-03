#include "LotsOfLines/CSVFileLoader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace LotsOfLines;

bool CSVFileLoader::supportsFormat(const std::string& path)
{
	return path.find(".csv") != path.npos;
}

std::shared_ptr<DataSet> CSVFileLoader::loadData(const std::string& path, const LoadOptions& options, ProgressMessage* progress) const
{
	std::ifstream in(path);
	if (in)
	{
		// Init dataset and other variables
		std::shared_ptr<DataSet> dataSet = std::make_shared<DataSet>();
		std::string line{ "" };
		std::istringstream is;

		// Get line count. Necessary evil. Start at 1 just to overshoot and make sure not 0
		int linecount = 1;
		while (std::getline(in, line)) linecount++;
		in.clear();
		in.seekg(0, std::ios::beg);

		// Skip first line for CSV format
		std::getline(in, line);

		Vector vec;
		std::string dataClass, token;
		double xn;
		int column = 0, columncount = 0, currentLine = 0;
		std::vector<unsigned int> ignoreColumns;
		//ignoreColumns.push_back(3);
		while (in >> line) {
			currentLine++;
			// Update progress
			if (progress) {
				const int progression = (int)(currentLine / (double)linecount * 100);
				progress->progress(progression);
			}
			if (line.empty()) continue;

			dataClass = "default";
			vec.clear();

			is.str(line);
			is.clear();

			while (std::getline(is, token, ',')) {
				// Skip column if in ignoreColumn
				if (std::find(ignoreColumns.begin(), ignoreColumns.end(), column) != ignoreColumns.end())
				{
					continue;
				}
				// Set dataclass to column if selected
				else if (column++ == options.classColumn) {
					dataClass = token;
					continue;
				}
				try
				{
					xn = std::stod(token);
					vec.push_back(xn);
				}
				catch (std::invalid_argument e)
				{
					// Empty column. Need to deal with this.
					if (token.empty())
					{
						vec.push_back(0.0);
						continue;
					}
					//If not double, then attempt to convert to an appropriate numeric value
					std::string months[]{ "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };
					std::string days[]{ "sun", "mon", "tue", "wed", "thu", "fri", "sat" };

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
				catch (std::out_of_range e)
				{
					std::cout << e.what() << std::endl;
				}
			}
			// Get column/variable count based off of first vector
			if (currentLine == 1) columncount = column;
			// Invalid vector size in comparison
			else if (columncount != column) return nullptr;
			// Reset column and add to dataset
			column = 0;
			dataSet->addVector(vec, dataClass);
		}
		in.close();
		return dataSet;
	}
	return nullptr;
}