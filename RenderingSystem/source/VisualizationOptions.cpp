#include "LotsOfLines/VisualizationOptions.hpp"

using namespace LotsOfLines;

bool VisualizationOptions::setInt(const std::string& name, int val)
{
	if (!setOptionType(name, EOT_INTEGER)) return false;

	m_integerOptions[name] = val;

	return true;
}

bool VisualizationOptions::setDouble(const std::string& name, double val)
{
	if (!setOptionType(name, EOT_DOUBLE)) return false;

	m_doubleOptions[name] = val;

	return true;
}

bool VisualizationOptions::setString(const std::string& name, const std::string& val)
{
	if (!setOptionType(name, EOT_STRING)) return false;

	m_stringOptions[name] = val;

	return true;
}

int VisualizationOptions::getInt(const std::string& name, int defaultVal)
{
	std::map<std::string, int>::iterator iter = m_integerOptions.find(name);
	return (iter != m_integerOptions.end()) ? iter->second : defaultVal;
}

double VisualizationOptions::getDouble(const std::string& name, double defaultVal)
{
	std::map<std::string, double>::iterator iter = m_doubleOptions.find(name);
	return (iter != m_doubleOptions.end()) ? iter->second : defaultVal;
}

std::string VisualizationOptions::getString(const std::string& name, const std::string& defaultVal)
{
	std::map<std::string, std::string>::iterator iter = m_stringOptions.find(name);
	return (iter != m_stringOptions.end()) ? iter->second : defaultVal;
}

bool VisualizationOptions::setOptionType(const std::string& name, E_OPTION_TYPE type)
{
	if (getOptionType(name) == EOT_UNKNOWN)
	{
		m_optionTypes[name] = type;
		return true;
	}

	return false;
}

E_OPTION_TYPE VisualizationOptions::getOptionType(const std::string& name)
{
	std::map<std::string, E_OPTION_TYPE>::iterator iter = m_optionTypes.find(name);
	return (iter != m_optionTypes.end()) ? iter->second : EOT_UNKNOWN;
}

const OptionTypeMap& VisualizationOptions::listOptions()
{
	return m_optionTypes;
}
