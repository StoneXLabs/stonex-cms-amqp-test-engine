#pragma once
#include <boost/json.hpp>

#include "Configuration/CMSWrapperConfiguration.h"
#include "Configuration/ConnectionConfiguration.h"
#include "Configuration/SessionConfiguration.h"
#include "Configuration/ConsumerConfiguration.h"
#include "Configuration/ProducerConfiguration.h"

class CMSWrapperConfigurationParser
{
public:
	CMSWrapperConfiguration createCMSConfig(const boost::json::value& json) const;
	ConnectionConfiguration  createConnectionConfig(const std::string& configName, const boost::json::value& json) const;
	SessionConfiguration createSessionConfig(const std::string& configName, const boost::json::value& json) const;
	ConsumerConfiguration createConsumerConfig(const std::string& configName, const boost::json::value& json) const;
	ProducerConfiguration createProducerConfig(const std::string& configName, const boost::json::value& json) const;
};

