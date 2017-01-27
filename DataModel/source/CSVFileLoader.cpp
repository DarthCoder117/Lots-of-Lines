#include "LotsOfLines/CSVFileLoader.hpp"
#include <fstream>
#include <regex>
#include <iostream>

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
		std::getline(in, line);

		// Start from second line
		while (!in.eof())
		{
			std::getline(in, line);
			if (line.empty()) continue;

			//Each line is a new vector
			Vector vec;
			std::string dataClass = "default";

			//Tokenize and convert to double.
			std::regex regex("[,]");
			std::sregex_token_iterator iter(line.begin(), line.end(), regex, -1);
			std::sregex_token_iterator end;
			while (iter != end)
			{
				std::string token = iter->str();

				//First try converting the token to a double and adding it to the vector
				try
				{
					double xn = std::stod(token);
					vec.push_back(xn);
				}
				catch (std::invalid_argument e)
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

					//No more conversions
					//Value is not added to vector
				}
				catch (std::out_of_range e)
				{
					std::cout << e.what() << "\n";
				}

				iter++;
			}

			//Add vector data
			dataSet->addVector(vec, dataClass);
		}

		return dataSet;
	}

	return nullptr;
}