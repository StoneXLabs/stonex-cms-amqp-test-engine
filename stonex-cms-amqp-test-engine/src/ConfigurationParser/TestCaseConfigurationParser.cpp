#include <ConfigurationParser/TestCaseConfigurationParser.h>

TestCaseConfiguration TestCaseConfigurationParser::createTestCaseConfig(const std::string & configName, const boost::json::value & json) const
{
	bool enabled{ false };
	std::string test_name{ "not initialized" };
	


	if (json.is_object())
	{
		auto configJson = json.as_object();
		if (auto test_name_val = configJson.if_contains("test_name"); test_name_val != nullptr && test_name_val->is_string())
			test_name = test_name_val->as_string().c_str();

		if (auto test_enabled_val = configJson.if_contains("enabled"); test_enabled_val != nullptr && test_enabled_val->is_bool())
			enabled = test_enabled_val->as_bool();

		boost::json::value verifierConfigJson;

		if (auto test_enabled_val = configJson.if_contains("expected"); test_enabled_val != nullptr && test_enabled_val->is_object())
		 verifierConfigJson = test_enabled_val->as_object();

		boost::json::value wrapperConfigJson;

		if (auto test_enabled_val = configJson.if_contains("cms_configuration"); test_enabled_val != nullptr && test_enabled_val->is_object())
			wrapperConfigJson = test_enabled_val->as_object();

		boost::json::value performerConfigJson;

		if (auto test_enabled_val = configJson.if_contains("message_parameters"); test_enabled_val != nullptr && test_enabled_val->is_object())
			performerConfigJson = test_enabled_val->as_object();

		return TestCaseConfiguration(configName, test_name, enabled, createWrapperConfiguration(configJson), createTestPerformerConfig(configJson), createTestVerifierConfig(configJson));

	}

	return TestCaseConfiguration(configName, test_name, enabled, createWrapperConfiguration(json), createTestPerformerConfig(json), createTestVerifierConfig(json));

}

TestCasePerformerConfiguration TestCaseConfigurationParser::createTestPerformerConfig(const boost::json::value & json) const
{
	std::vector<MessageSenderConfiguration*> configurationParams;

	if (json.is_object())
	{
		if (auto test_params_val = json.as_object().if_contains("message_parameters"); test_params_val != nullptr && test_params_val->is_object())
		{
			std::transform(std::begin(test_params_val->as_object()), std::end(test_params_val->as_object()), std::back_inserter(configurationParams), [this](const boost::json::object::value_type item) {
				return createTestCaseProducerConfig(item.key_c_str(), item.value());
			});

			//std::for_each(std::begin(test_params_val->as_object()), std::end(test_params_val->as_object()), [&par, this](const boost::json::object::value_type item) {
			//	auto prod_params = createTestCaseProducerConfig(item.key_c_str(), item.value());
			//	par.addProducerMessagesParameter(prod_params);
			//});
		}
	}

	return configurationParams;
}

TestCaseVerifierConfiguration TestCaseConfigurationParser::createTestVerifierConfig(const boost::json::value & json) const
{
	std::vector<MessageReceiverConfiguration*> receiverConfigs;
	std::vector<ExceptionsConfiguration*> exceptionsConfig;

	if (json.is_object())
	{
		if (auto test_expected_val = json.as_object().if_contains("expected"); test_expected_val != nullptr && test_expected_val->is_object())
		{
			if (auto test_expected_messages_val = test_expected_val->as_object().if_contains("messages"); test_expected_messages_val != nullptr && test_expected_messages_val->is_object())
			{
				std::transform(std::cbegin(test_expected_messages_val->as_object()), std::cend(test_expected_messages_val->as_object()), std::back_inserter(receiverConfigs), [this](const boost::json::object::value_type& obj) {
					return createTestCaseReceiverConfig(obj.key_c_str(), obj.value());
				});
			}

			if (auto test_expected_exceptions_val = test_expected_val->as_object().if_contains("exceptions"); test_expected_exceptions_val != nullptr && test_expected_exceptions_val->is_object())
			{
				std::transform(std::cbegin(test_expected_exceptions_val->as_object()), std::cend(test_expected_exceptions_val->as_object()), std::back_inserter(exceptionsConfig), [this](const boost::json::object::value_type& obj) {
					return createTestExceptionConfig(obj.key_c_str(), obj.value());
				});
			}
		}
	}

	return TestCaseVerifierConfiguration(receiverConfigs, exceptionsConfig);
}
