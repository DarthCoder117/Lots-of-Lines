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

		// Get start pos and end byte pos for progress indication
		std::streampos start = in.tellg(), current = in.tellg();
		in.seekg(0, std::ios::end);
		std::streampos end = in.tellg();
		in.clear();
		in.seekg(0, std::ios::beg);

		// Skip first line for CSV format
		std::getline(in, line);

		// Necessary initialized items (do outside of loop)
		Vector vec;
		std::string dataClass, token;
		double xn;
		int column = 0, columncount = 0, currentLine = 0;
		// For numeric conversions
		std::string months[]{ "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };
		std::string days[]{ "sun", "mon", "tue", "wed", "thu", "fri", "sat" };
		ptrdiff_t month_pos, day_pos;
		// Hard coded ignorecolumns
		std::vector<unsigned int> ignoreColumns;
		//ignoreColumns.push_back(3);
		while (in >> line) {
			currentLine++;
			// Update progress
			if (progress) {
				current = in.tellg();
				progress->progress((current - start) / (double)(end - start) * 100);
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
					//Try month or day conversion
					month_pos = std::find(std::begin(months), std::end(months), token) - std::begin(months);
					day_pos = std::find(std::begin(days), std::end(days), token) - std::begin(days);
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
			if (currentLine == 1) columncount = vec.size();
			// Invalid vector size in comparison
			else if (columncount != vec.size()) return nullptr;
			// Reset column and add to dataset
			column = 0;
			dataSet->addVector(vec, dataClass);
		}
		in.close();
		return dataSet;
	}
	return nullptr;
}