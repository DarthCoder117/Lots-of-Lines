#include "LotsOfLines/DataFileLoader.hpp"
#include <fstream>
#include <regex>
#include <iostream>
#include <sstream>

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

		std::string line{ "" };
		std::istringstream is, linestream;

		// Declare items outside of loop
		Vector vec;
		std::string dataClass, token;
		double xn;

		//// BUFFER ATTEMPT ////
		//// Create buffer
		//constexpr size_t bufferSize = 1024;
		//char buffer[bufferSize];

		//while (in.good())
		//{
		//	in.read(buffer, bufferSize);
		//	dataClass = "default";

		//	is.str(buffer);
		//	is.clear();

		//	while (std::getline(is, line)) {
		//		linestream.str(line);
		//		linestream.clear();
		//		vec.clear();
		//		while (std::getline(linestream, token, ',')) {
		//			//First try converting the token to a double and adding it to the vector
		//			try
		//			{
		//				xn = std::stod(token);
		//				vec.push_back(xn);
		//			}
		//			catch (std::invalid_argument e)
		//			{
		//				//If conversion fails then check to see if we're at the end.
		//				if (is.peek() != ',')
		//				{
		//					//If so, then this token is the data class label.
		//					dataClass = token;
		//				}
		//			}
		//			catch (std::out_of_range e)
		//			{
		//				std::cout << e.what() << "\n";
		//			}
		//		}
		//		//Add vector data
		//		dataSet->addVector(vec, dataClass);
		//	}
		//}
		//free(buffer);

		// Current optimal loading
		while (in >> line) {
			if (line.empty()) continue;

			dataClass = "default";
			vec.clear();

			is.str(line);
			is.clear();

			std::string token;

			while (std::getline(is, token, ',')) {
				//First try converting the token to a double and adding it to the vector
				try
				{
					xn = std::stod(token);
					vec.push_back(xn);
				}
				catch (std::invalid_argument e)
				{
					//If conversion fails then check to see if we're at the end.
					if (is.peek() != ',')
					{
						//If so, then this token is the data class label.
						dataClass = token;
					}
				}
				catch (std::out_of_range e)
				{
					std::cout << e.what() << "\n";
				}
			}

			//Add vector data
			dataSet->addVector(vec, dataClass);
		}
		return dataSet;
	}
	return nullptr;
}