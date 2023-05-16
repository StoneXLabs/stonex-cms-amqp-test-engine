#pragma once
#include <boost/json.hpp>

#include "..\Configuration\MessageSenderConfiguration.h"
#include <ConfigurationParser/MessageDecoratorConfigurationParser.h>

class TestCaseProducerConfigurationParser : public MessageDecoratorConfigurationParser
{
public:
	virtual MessageSenderConfiguration* createTestCaseProducerConfig(const std::string& configName, const boost::json::value& json) const;


};

