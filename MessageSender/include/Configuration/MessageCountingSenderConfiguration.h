#pragma once

#include "MessageSenderConfiguration.h"
#include "EventCounter.h"

class MessageCountingSenderConfiguration : public MessageSenderConfiguration, public EventCounter
{
public:
	MessageCountingSenderConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& producerId, long long message_count);
	friend bool operator== (const MessageCountingSenderConfiguration& lhs, const MessageCountingSenderConfiguration& rhs);
};

