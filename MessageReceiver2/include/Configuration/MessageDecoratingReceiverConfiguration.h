#pragma once
#include "MessageReceiverConfiguration.h"
#include <Configuration/MessageDecoratorConfiguration.h>

class MessageDecoratingReceiverConfiguration : public MessageReceiverConfiguration, public MessageDecoratorConfiguration
{
public:
	MessageDecoratingReceiverConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& consumerId, const std::vector<MessageTestField*>& decorations);
	friend bool operator== (const MessageDecoratingReceiverConfiguration& lhs, const MessageDecoratingReceiverConfiguration& rhs);

};