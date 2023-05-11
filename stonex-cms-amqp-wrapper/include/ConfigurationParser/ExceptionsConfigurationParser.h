#pragma once
#include "..\Configuration\ExceptionsConfiguration.h"
#include <boost/json.hpp>

class ExceptionsConfigurationParser
{
public:
	ExceptionsConfiguration* createTestExceptionConfig(const std::string& configName, const boost::json::value& json) const;

};

