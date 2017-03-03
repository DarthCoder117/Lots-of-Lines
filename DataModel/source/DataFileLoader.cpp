#include "LotsOfLines/DataFileLoader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

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

		// Get line count. Necessary evil. Start at 1 just to overshoot and make sure not 0
		int linecount = 1;
		while (std::getline(in, line)) linecount++;
		in.clear();
		in.seekg(0, std::ios::beg);

		// Declare items outside of loop
		Vector vec;
		std::string dataClass, token;
		double xn;

		////// BUFFER ATTEMPT ////
		//// Create buffer
		//char *buffer = (char *)malloc(sizeof(char) * (length + 1));

		//// Read in the whole file
		//in.read(buffer, length);	
		//// Null terminate the buffer
		//buffer[length] = '\0';
		//// Default class name
		//dataClass = "default";

		//// Set buffer to stream
		//is.str(buffer);
		//is.clear();

		//int column = 0, classC = 0;
		//while (std::getline(is, line)) {
		//	// Check it has data
		//	if (line.empty()) continue;
		//	// Set line to stream
		//	linestream.str(line);
		//	linestream.clear();
		//	vec.clear();
		//	while (std::getline(linestream, token, ',')) {
		//		//Initally remove any trailing char
		//		if (!token.empty() && token[token.size() - 1] == '\r')
		//			token.erase(token.size() - 1);
		//		//Convert to class
		//		//if (column == classC) dataClass = token;
		//		//First try converting the token to a double and adding it to the vector
		//		//else {
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
		//		//}
		//		column++;
		//	}
		//	column = 0;
		//	//Add vector data
		//	dataSet->addVector(vec, dataClass);
		//}
		//free(buffer);
		
		// Current optimal loading
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
				if (column++ == options.classColumn) {
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
					std::cout << e.what() << "\n";
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