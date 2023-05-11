#pragma once

#include "TestCaseProducerConfiguration.h"
#include "EventCounter.h"

class CountingCaseProducerConfiguration : public TestCaseProducerConfiguration, public EventCounter
{
public:
	CountingCaseProducerConfiguration(const std::string& producerId, const std::string& sessionId, long long message_count);
	friend bool operator== (const CountingCaseProducerConfiguration& lhs, const CountingCaseProducerConfiguration& rhs);
};

