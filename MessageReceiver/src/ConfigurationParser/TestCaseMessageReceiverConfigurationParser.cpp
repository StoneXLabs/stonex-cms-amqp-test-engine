#include <ConfigurationParser/TestCaseMessageReceiverConfigurationParser.h>

TestCaseMessageReceiverConfiguration * TestCaseMessageReceiverConfigurationParser::createTestReceiverConfig(const std::string & configName, const boost::json::value & json) const
{
	if (json.is_object())
	{

		if (json.as_object().size() != 2)
			return nullptr;

		std::string connection;
		std::string session;

		if (auto connection_id = json.as_object().if_contains("connection"); connection_id && connection_id->is_string())
			connection = connection_id->as_string().c_str();
		else
			return nullptr;

		if (auto session_id = json.as_object().if_contains("session"); session_id && session_id->is_string())
			session = session_id->as_string().c_str();
		else
			return nullptr;
	
		return new TestCaseMessageReceiverConfiguration(connection, session, configName);
	}
	else
		return nullptr;
}
