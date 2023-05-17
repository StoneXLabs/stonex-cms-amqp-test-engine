#pragma once
#include "MessageSenderConfiguration.h"
#include <utils/EventCounter.h>
#include <Configuration/MessageDecoratorConfiguration.h>

class MessageCountingDecoratingSenderConfiguration : public MessageSenderConfiguration, public EventCounter, public MessageDecoratorConfiguration
{
public:
	MessageCountingDecoratingSenderConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& producerId, long long message_count, const std::vector<MessageTestField*>& decorations);
	friend bool operator== (const MessageCountingDecoratingSenderConfiguration& lhs, const MessageCountingDecoratingSenderConfiguration& rhs);
};

