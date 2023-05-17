#pragma once
#include <boost/json.hpp>

#include "..\Configuration\MessageReceiverConfiguration.h"
#include <ConfigurationParser/MessageDecoratorConfigurationParser.h>

class TestCaseReceiverConfigurationParser : public MessageDecoratorConfigurationParser
{
public:
	virtual MessageReceiverConfiguration* createTestCaseReceiverConfig(const std::string& configName, const boost::json::value& json) const;


};

