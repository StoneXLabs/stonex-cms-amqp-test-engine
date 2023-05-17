#pragma once
#include "MessageReceiverConfiguration.h"
#include <utils/EventCounter.h>
#include <Configuration/MessageDecoratorConfiguration.h>

class MessageCountingDecoratingReceiverConfiguration : public MessageReceiverConfiguration, public EventCounter, public MessageDecoratorConfiguration
{
public:
	MessageCountingDecoratingReceiverConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& consumerId, long long message_count, const std::vector<MessageTestField*>& decorations);
	friend bool operator== (const MessageCountingDecoratingReceiverConfiguration& lhs, const MessageCountingDecoratingReceiverConfiguration& rhs);
};

