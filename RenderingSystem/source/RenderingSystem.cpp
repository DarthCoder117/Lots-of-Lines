#include "LotsOfLines/RenderingSystem.hpp"

using namespace LotsOfLines;

RenderingSystem::RenderingSystem(IRenderer* driver)
	:m_driver(driver)
{
	
}


IRenderer* RenderingSystem::getDriver() const
{
	return m_driver;
}

// TEMPORARY FOR GHETTO TESTING PURPOSES. TESTS WILL BE MOVED TO THE TEST FRAMEWORK SHORTLY.
int main()
{
	return 0;
}
