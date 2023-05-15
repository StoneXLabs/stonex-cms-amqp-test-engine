#include <ConfigurationParser/TestCaseProducerConfigurationParser.h>
#include <Configuration/FileTestCaseProducerConfiguration.h>
#include <Configuration/CountingCaseProducerConfiguration.h>
#include <Configuration/FileCountingTestCaseProducerConfiguration.h>
#include <Configuration/TestCaseDecoratingProducerConfiguration.h>


TestCaseProducerConfiguration * TestCaseProducerConfigurationParser::createTestCaseProducerConfig(const std::string & configName, const boost::json::value & json) const
{
	if (json.is_object())
	{
		if (json.as_object().size() < 2)
			return nullptr;

		std::string message_factory;
		std::string session_factory;



		if (auto session_factory_id = json.as_object().if_contains("session_factory"); session_factory_id && session_factory_id->is_string())
			session_factory = session_factory_id->as_string().c_str();
		else
			return nullptr;

		if (auto message_factory_id = json.as_object().if_contains("message_factory"); message_factory_id && message_factory_id->is_string())
			message_factory = message_factory_id->as_string().c_str();
		else
			return nullptr;

		if (json.as_object().size() == 2)
		{
								
			return new TestCaseProducerConfiguration(session_factory, message_factory, configName);
		} 
		else if (json.as_object().size() == 3)
		{

			if (auto tmp_message_file = json.as_object().if_contains("message_file"); tmp_message_file && tmp_message_file->is_string()) {

				std::string message_file;
				message_file = tmp_message_file->as_string().c_str();
				return new FileTestCaseProducerConfiguration(session_factory, message_factory, configName, message_file);
			}
			else if (auto tmp_message_count = json.as_object().if_contains("message_count"); tmp_message_count && tmp_message_count->is_int64())
			{
				int message_count{ 0 };
				message_count = tmp_message_count->as_int64();
				return new CountingCaseProducerConfiguration(session_factory, message_factory, configName, message_count);
			}
			else if (auto tmp_message_properties = json.as_object().if_contains("properties"); tmp_message_properties && tmp_message_properties->is_object())
			{
				//auto message_properties = tmp_message_properties;
				auto decorator_configuration = createMessgeDecoratorConfiguration("properties", *tmp_message_properties);
				return new TestCaseDecoratingProducerConfiguration(session_factory, message_factory, configName, decorator_configuration.decorations());
			}
			else
				return nullptr;

		}
		else if (json.as_object().size() == 4)
		{
			std::string message_file;
			int message_count{ 0 };

			if (auto tmp_message_file = json.as_object().if_contains("message_file"); tmp_message_file && tmp_message_file->is_string())
			{
				message_file = tmp_message_file->as_string().c_str();
			}
			else
				return nullptr;

			if (auto tmp_message_count = json.as_object().if_contains("message_count"); tmp_message_count && tmp_message_count->is_int64()) 
			{
				message_count = tmp_message_count->as_int64();
			}
			else
				return nullptr;

			return new FileCountingTestCaseProducerConfiguration(session_factory, message_factory, configName, message_file,message_count);
		}
		return nullptr;
	}
	else
		return nullptr;
}


