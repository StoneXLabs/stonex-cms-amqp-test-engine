#pragma once
#include <boost/json.hpp>
#include "../Configuration/TestCaseMessageReceiverConfiguration.h"

class TestCaseMessageReceiverConfigurationParser
{
public:
	virtual TestCaseMessageReceiverConfiguration* createTestReceiverConfig(const std::string& configName, const boost::json::value& json) const;

};

