#pragma once
#include <Configuration/TestCaseConfiguration.h>
#include <Configuration/TestCasePerformerConfiguration.h>
#include <Configuration/TestCaseVerifierConfiguration.h>

#include <ConfigurationParser/WrapperConfigurationParser.h>
#include <ConfigurationParser/TestCaseProducerConfigurationParser.h>
#include <ConfigurationParser/TestCaseReceiverConfigurationParser.h>
#include <ConfigurationParser/ExceptionsConfigurationParser.h>

#include <boost/json.hpp>

class TestCaseConfigurationParser : public WrapperConfigurationParser, public TestCaseProducerConfigurationParser, public TestCaseReceiverConfigurationParser, public ExceptionsConfigurationParser
{
public:
	TestCaseConfiguration createTestCaseConfig(const std::string& configName, const boost::json::value& json) const;

private:
	TestCasePerformerConfiguration createTestPerformerConfig(const boost::json::value & json) const;
	TestCaseVerifierConfiguration createTestVerifierConfig(const boost::json::value & json) const;
};

