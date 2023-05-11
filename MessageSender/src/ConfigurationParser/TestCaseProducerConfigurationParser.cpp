#include <ConfigurationParser/TestCaseProducerConfigurationParser.h>
#include <Configuration/FileTestCaseProducerConfiguration.h>
#include <Configuration/CountingCaseProducerConfiguration.h>
#include <Configuration/FileCountingTestCaseProducerConfiguration.h>


TestCaseProducerConfiguration * TestCaseProducerConfigurationParser::createTestCaseProducerConfig(const std::string & configName, const boost::json::value & json) const
{
	if (json.is_object())
	{
		if (json.as_object().size() == 1)
		{
			std::string message_factory;

			if (auto tmp_message_file = json.as_object().if_contains("message_factory"); tmp_message_file && tmp_message_file->is_string())
				message_factory = tmp_message_file->as_string().c_str();
						
			return new TestCaseProducerConfiguration(configName, message_factory);
		} 
		else if (json.as_object().size() == 2)
		{
			std::string message_factory;

			if (auto tmp_message_file = json.as_object().if_contains("message_factory"); tmp_message_file && tmp_message_file->is_string())
				message_factory = tmp_message_file->as_string().c_str();

			if (auto tmp_message_file = json.as_object().if_contains("message_file"); tmp_message_file && tmp_message_file->is_string()) {

				std::string message_file;
				message_file = tmp_message_file->as_string().c_str();
				return new FileTestCaseProducerConfiguration(configName, message_factory, message_file);
			}
			else if (auto tmp_message_count = json.as_object().if_contains("message_count"); tmp_message_count && tmp_message_count->is_int64())
			{
				int message_count{ 0 };
				message_count = tmp_message_count->as_int64();
				return new CountingCaseProducerConfiguration(configName, message_factory, message_count);
			}

		}
		else if (json.as_object().size() == 3)
		{
			std::string message_file;
			std::string message_factory;
			int message_count{ 0 };

			if (auto tmp_message_file = json.as_object().if_contains("message_factory"); tmp_message_file && tmp_message_file->is_string())
				message_factory = tmp_message_file->as_string().c_str();

			if (auto tmp_message_file = json.as_object().if_contains("message_file"); tmp_message_file && tmp_message_file->is_string())
				message_file = tmp_message_file->as_string().c_str();

			if (auto tmp_message_count = json.as_object().if_contains("message_count"); tmp_message_count && tmp_message_count->is_int64())
				message_count = tmp_message_count->as_int64();

			return new FileCountingTestCaseProducerConfiguration(configName, message_factory, message_file,message_count);
		}
		return nullptr;
	}
	else
		return nullptr;
}


