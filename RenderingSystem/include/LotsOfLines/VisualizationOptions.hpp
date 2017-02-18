#ifndef VISUALIZATION_OPTIONS_HPP
#define VISUALIZATION_OPTIONS_HPP
#include <map>
#include <vector>

namespace LotsOfLines
{
	enum E_OPTION_TYPE
	{
		EOT_INTEGER,
		EOT_DOUBLE,
		EOT_STRING,
		EOT_BOOL,
		EOT_UNKNOWN
	};

	typedef std::map<std::string, E_OPTION_TYPE> OptionTypeMap;

	///@brief Generic options class for visualizations.
	class VisualizationOptions
	{
	public:

		///@brief Set an integer option
		///@return True on success, or returns false if the option has already been set as a different type.
		bool setInt(const std::string& name, int val);
		///@brief Set a double option
		///@return True on success, or returns false if the option has already been set as a different type.
		bool setDouble(const std::string& name, double val);
		///@brief Set a string option
		///@return True on success, or returns false if the option has already been set as a different type.
		bool setString(const std::string& name, const std::string& val);
		///@brief Set a boolean option
		///@return True on success, or returns false if the option has already been set as a different type.
		bool setBool(const std::string& name, bool val);

		///@return The value of the named integer option, or the specified default if it doesn't exist.
		int getInt(const std::string& name, int defaultVal = 0);
		///@return The value of the named double option, or the specified default if it doesn't exist.
		double getDouble(const std::string& name, double defaultVal = 0);
		///@return The value of the named string option, or the specified default if it doesn't exist.
		std::string getString(const std::string& name, const std::string& defaultVal = "");
		///@return The value of the named bool option, or the specified default if it doesn't exist.
		bool getBool(const std::string& name, bool defaultVal = false);

		///@return The type of the named option.
		E_OPTION_TYPE getOptionType(const std::string& name);

		///@return Map of all option names and their types.
		const OptionTypeMap& listOptions();

	private:

		OptionTypeMap m_optionTypes;//< Option name to type mapping

		bool setOptionType(const std::string& name, E_OPTION_TYPE type);

		std::map<std::string, int> m_integerOptions;
		std::map<std::string, double> m_doubleOptions;
		std::map<std::string, std::string> m_stringOptions;
		std::map<std::string, bool> m_boolOptions;
	};
}

#endif