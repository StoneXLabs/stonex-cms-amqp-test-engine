#include <Configuration/MessageCountingDecoratingReceiverConfiguration.h>

MessageCountingDecoratingReceiverConfiguration::MessageCountingDecoratingReceiverConfiguration(const std::string & connectionId, const std::string & sessionId, const std::string & consumerId, long long message_count, const std::vector<MessageTestField*>& decorations)
	:MessageReceiverConfiguration(connectionId, sessionId, consumerId),
	EventCounter(message_count),
	MessageDecoratorConfiguration(decorations)

{
}

bool operator==(const MessageCountingDecoratingReceiverConfiguration & lhs, const MessageCountingDecoratingReceiverConfiguration & rhs)
{
	return lhs.connectionId() == rhs.connectionId() &&
		lhs.sessionId() == rhs.sessionId() &&
		lhs.consumerId() == rhs.consumerId() &&
		rhs.expectedEventCount() == lhs.expectedEventCount() &&
		std::equal(std::cbegin(lhs.decorations()), std::cend(lhs.decorations()), std::cbegin(rhs.decorations()), std::cend(rhs.decorations()), [](const MessageTestField* lhs_item, const MessageTestField* rhs_item) {return *lhs_item == *rhs_item; });
}
