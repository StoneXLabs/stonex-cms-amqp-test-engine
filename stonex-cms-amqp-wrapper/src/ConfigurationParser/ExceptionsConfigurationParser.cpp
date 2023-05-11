#include <ConfigurationParser/ExceptionsConfigurationParser.h>

ExceptionsConfiguration * ExceptionsConfigurationParser::createTestExceptionConfig(const std::string & configName, const boost::json::value & json) const
{
	if (json.is_object())
	{
		int expected_count{ -1 };

		if (auto tmp_expected_count = json.as_object().if_contains("count"); tmp_expected_count && tmp_expected_count->is_int64())
			expected_count = tmp_expected_count->as_int64();

		return new ExceptionsConfiguration(configName, expected_count);

	}
	else
		return nullptr;
}
