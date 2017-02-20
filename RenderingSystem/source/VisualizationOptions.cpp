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

bool VisualizationOptions::setBool(const std::string& name, bool val)
{
	if (!setOptionType(name, EOT_BOOL)) return false;

	m_boolOptions[name] = val;

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

bool VisualizationOptions::getBool(const std::string& name, bool defaultVal)
{
	std::map<std::string, bool>::iterator iter = m_boolOptions.find(name);
	return (iter != m_boolOptions.end()) ? iter->second : defaultVal;
}

void VisualizationOptions::clear()
{
	m_integerOptions.clear();
	m_stringOptions.clear();
	m_doubleOptions.clear();
	m_boolOptions.clear();
}

bool VisualizationOptions::setOptionType(const std::string& name, E_OPTION_TYPE type)
{
	E_OPTION_TYPE existingType = getOptionType(name);
	if (existingType == EOT_UNKNOWN)
	{
		m_optionTypes[name] = type;
		return true;
	}
	else if (existingType == type)
	{
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
