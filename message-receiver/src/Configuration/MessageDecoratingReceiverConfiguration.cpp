#include <Configuration/MessageDecoratingReceiverConfiguration.h>

MessageDecoratingReceiverConfiguration::MessageDecoratingReceiverConfiguration(const std::string & connectionId, const std::string & sessionId, const std::string & consumerId, const std::vector<MessageTestField*>& decorations)
	:MessageReceiverConfiguration(connectionId, sessionId, consumerId),
	MessageDecoratorConfiguration(decorations)
{
}

bool operator==(const MessageDecoratingReceiverConfiguration & lhs, const MessageDecoratingReceiverConfiguration & rhs)
{
	return lhs.connectionId() == rhs.connectionId() &&
		lhs.sessionId() == rhs.sessionId() &&
		lhs.consumerId() == rhs.consumerId() &&
		std::equal(std::cbegin(lhs.decorations()), std::cend(lhs.decorations()), std::cbegin(rhs.decorations()), std::cend(rhs.decorations()), [](const MessageTestField* lhs_item, const MessageTestField* rhs_item) {return *lhs_item == *rhs_item; });
}
