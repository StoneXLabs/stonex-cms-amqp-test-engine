#pragma once

#include "TestCaseProducerConfiguration.h"
#include "EventCounter.h"

class CountingCaseProducerConfiguration : public TestCaseProducerConfiguration, public EventCounter
{
public:
	CountingCaseProducerConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& producerId, long long message_count);
	friend bool operator== (const CountingCaseProducerConfiguration& lhs, const CountingCaseProducerConfiguration& rhs);
};

