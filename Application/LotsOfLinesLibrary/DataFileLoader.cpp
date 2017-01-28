#include "DataFileLoader.h"
#include <fstream>
#include <regex>
#include <iostream>

using namespace LotsOfLines;

bool DataFileLoader::supportsFormat(const std::string& path)
{
	return path.find(".data") != path.npos;
}

std::shared_ptr<DataSet> DataFileLoader::loadData(const std::string& path, const LoadOptions& options) const
{
	std::ifstream in(path);
	if (in)
	{
		std::shared_ptr<DataSet> dataSet = std::make_shared<DataSet>();

		while (!in.eof())
		{
			std::string line{ "" };
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
					//If conversion fails then check to see if we're at the end.
					std::sregex_token_iterator next = iter;
					next++;
					if (next == end)
					{
						//If so, then this token is the data class label.
						dataClass = token;
					}
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