#pragma once
#include "MessageSenderConfiguration.h"
#include <Configuration/MessageDecoratorConfiguration.h>

class MessageDecoratingSenderConfiguration : public MessageSenderConfiguration, public MessageDecoratorConfiguration
{
public:
	MessageDecoratingSenderConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& producerId, const std::vector<MessageTestField*>& decorations);
	friend bool operator== (const MessageDecoratingSenderConfiguration& lhs, const MessageDecoratingSenderConfiguration& rhs);

};