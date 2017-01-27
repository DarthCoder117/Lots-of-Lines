#include "catch.hpp"
#include <Windows.h>
#include "LotsOfLines/DataModel.hpp"
#include "LotsOfLines/DataFileLoader.hpp"
#include "LotsOfLines/CSVFileLoader.hpp"
#include <fstream>

using namespace LotsOfLines;

//DataFileLoader
TEST_CASE("Load .data file", "[DataFileLoader]") 
{
	DataFileLoader fsLoader;
	DataModel dataModel
	({
		&fsLoader
	});

	dataModel.loadData("../../../tests/data/iris.data");
	printf("");

	/*REQUIRE(Factorial(1) == 1);
	REQUIRE(Factorial(2) == 2);
	REQUIRE(Factorial(3) == 6);
	REQUIRE(Factorial(10) == 3628800);*/
}

// CSVFileLoader
TEST_CASE("Load .csv file", "[CSVFileLoader]")
{
	CSVFileLoader fsLoader;
	DataModel dataModel
	({
		&fsLoader
	});

	dataModel.loadData("../../../tests/data/forestfires.csv", LoadOptions());
	printf("");
}