#include "LotsOfLines/DataFileLoader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h>

using namespace LotsOfLines;

bool DataFileLoader::supportsFormat(const std::string& path)
{
	return path.find(".data") != path.npos;
}

std::shared_ptr<DataSet> DataFileLoader::loadData(const std::string& path, const LoadOptions& options) const
{
	// Load file
	std::ifstream in(path, std::ios::binary);

	// Get file size
	std::streampos begin = in.tellg(), end;
	in.seekg(0, std::ios::end);
	end = in.tellg() - begin;
	in.seekg(0, std::ios::beg);
	off_t length = end - begin;

	if (in)
	{
		// Init dataset and other variables
		std::shared_ptr<DataSet> dataSet = std::make_shared<DataSet>();
		std::string line{ "" };
		std::istringstream is, linestream;

		// Declare items outside of loop
		Vector vec;
		std::string dataClass, token;
		double xn;

		//// BUFFER ATTEMPT ////
		// Create buffer
		char *buffer = (char *)malloc(sizeof(char) * (length + 1));

		// Read in the whole file
		in.read(buffer, length);	
		// Null terminate the buffer
		buffer[length] = '\0';
		// Default class name
		dataClass = "default";

		// Set buffer to stream
		is.str(buffer);
		is.clear();

		while (std::getline(is, line)) {
			// Check it has data
			if (line.empty()) continue;
			// Set line to stream
			linestream.str(line);
			linestream.clear();
			vec.clear();
			while (std::getline(linestream, token, ',')) {
				//Initally remove any trailing char
				if (!token.empty() && token[token.size() - 1] == '\r')
					token.erase(token.size() - 1);
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
		free(buffer);
		
		//// Current optimal loading
		//while (in >> line) {
		//	if (line.empty()) continue;

		//	dataClass = "default";
		//	vec.clear();

		//	is.str(line);
		//	is.clear();

		//	std::string token;

		//	while (std::getline(is, token, ',')) {
		//		//First try converting the token to a double and adding it to the vector
		//		try
		//		{
		//			xn = std::stod(token);
		//			vec.push_back(xn);
		//		}
		//		catch (std::invalid_argument e)
		//		{
		//			//If conversion fails then check to see if we're at the end.
		//			if (is.peek() != ',')
		//			{
		//				//If so, then this token is the data class label.
		//				dataClass = token;
		//			}
		//		}
		//		catch (std::out_of_range e)
		//		{
		//			std::cout << e.what() << "\n";
		//		}
		//	}

		//	//Add vector data
		//	dataSet->addVector(vec, dataClass);
		//}

		in.close();
		return dataSet;
	}
	return nullptr;
}