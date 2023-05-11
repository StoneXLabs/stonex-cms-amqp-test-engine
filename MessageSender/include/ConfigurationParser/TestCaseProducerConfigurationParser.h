#pragma once
#include <boost/json.hpp>

#include "..\Configuration\TestCaseProducerConfiguration.h"
class TestCaseProducerConfigurationParser
{
public:
	virtual TestCaseProducerConfiguration* createTestCaseProducerConfig(const std::string& configName, const boost::json::value& json) const;


};

