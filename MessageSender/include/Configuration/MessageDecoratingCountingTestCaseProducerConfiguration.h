#pragma once
#include "TestCaseProducerConfiguration.h"
#include "EventCounter.h"
#include <Configuration/MessageDecoratorConfiguration.h>

class MessageDecoratingCountingTestCaseProducerConfiguration : public TestCaseProducerConfiguration, public EventCounter, public MessageDecoratorConfiguration
{

	MessageDecoratingCountingTestCaseProducerConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& producerId, long long message_count, const std::vector<MessageTestField*>& decorations);
	friend bool operator== (const MessageDecoratingCountingTestCaseProducerConfiguration& lhs, const MessageDecoratingCountingTestCaseProducerConfiguration& rhs);
};

