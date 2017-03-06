#include "LotsOfLines/DataFileLoader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace LotsOfLines;

bool DataFileLoader::supportsFormat(const std::string& path)
{
	return path.find(".data") != path.npos;
}

std::shared_ptr<DataSet> DataFileLoader::loadData(const std::string& path, const LoadOptions& options, ProgressMessage* progress) const
{
	// Load file
	std::ifstream in(path, std::ios::binary);

	//// Get file size (for buffer)
	//std::streampos begin = in.tellg(), end;
	//in.seekg(0, std::ios::end);
	//end = in.tellg() - begin;
	//in.seekg(0, std::ios::beg);
	//off_t length = end - begin;

	if (in)
	{
		// Init dataset and other variables
		std::shared_ptr<DataSet> dataSet = std::make_shared<DataSet>();
	    std::string line{ "" };
		std::istringstream is, linestream;

		// Get start pos and end byte pos for progress indication
		std::streampos start = in.tellg(), current = in.tellg();
		in.seekg(0, std::ios::end);
		std::streampos end = in.tellg();
		in.clear();
		in.seekg(start);

		// Declare items outside of loop
		Vector vec;
		std::string dataClass, token;
		double xn;
		int column = 0, columncount = 0, currentLine = 0;

		// Determine class column
		int classColumn = options.classColumn;
		if (!options.customClassColumn)
		{
			std::getline(in, line);
			in.clear();
			in.seekg(start);
			classColumn = std::count(line.begin(), line.end(), ',');
		}

		// For numeric conversion
		std::string months[]{ "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };
		std::string days[]{ "sun", "mon", "tue", "wed", "thu", "fri", "sat" };
		ptrdiff_t month_pos, day_pos;
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
				if (column++ == classColumn) {
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
					std::cout << e.what() << "\n";
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