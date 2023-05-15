#pragma once
#include <boost/json.hpp>

#include "..\Configuration\TestCaseProducerConfiguration.h"
#include <ConfigurationParser/MessageDecoratorConfigurationParser.h>

class TestCaseProducerConfigurationParser : public MessageDecoratorConfigurationParser
{
public:
	virtual TestCaseProducerConfiguration* createTestCaseProducerConfig(const std::string& configName, const boost::json::value& json) const;


};

