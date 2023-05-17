#pragma once

#include "MessageReceiverConfiguration.h"
#include <utils/EventCounter.h>

class MessageCountingReceiverConfiguration : public MessageReceiverConfiguration, public EventCounter
{
public:
	MessageCountingReceiverConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& consumerId, long long message_count);
	friend bool operator== (const MessageCountingReceiverConfiguration& lhs, const MessageCountingReceiverConfiguration& rhs);
};

