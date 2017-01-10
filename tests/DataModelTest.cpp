#include "catch.hpp"
#include "LotsOfLines/DataModel.hpp"
#include "LotsOfLines/FileSystemLoader.hpp"

using namespace LotsOfLines;

//FileSystemLoader
TEST_CASE("Load .data file", "[FileSystemLoader]") 
{
	FileSystemLoader fsLoader;
	DataModel dataModel
	({
		&fsLoader
	});

	dataModel.loadData("C:/Users/super/Documents/School/CS 481/Lots-of-Lines/tests/data/iris.data");
	printf("");

	/*REQUIRE(Factorial(1) == 1);
	REQUIRE(Factorial(2) == 2);
	REQUIRE(Factorial(3) == 6);
	REQUIRE(Factorial(10) == 3628800);*/
}