#include <Configuration/MessageDecoratingSenderConfiguration.h>

MessageDecoratingSenderConfiguration::MessageDecoratingSenderConfiguration(const std::string & connectionId, const std::string & sessionId, const std::string & producerId, const std::vector<MessageTestField*>& decorations)
	:MessageSenderConfiguration(connectionId, sessionId, producerId),
	MessageDecoratorConfiguration(decorations)
{
}

bool operator==(const MessageDecoratingSenderConfiguration & lhs, const MessageDecoratingSenderConfiguration & rhs)
{
	return lhs.connectionId() == rhs.connectionId() &&
		lhs.sessionId() == rhs.sessionId() &&
		lhs.producerId() == rhs.producerId() &&
		std::equal(std::cbegin(lhs.decorations()), std::cend(lhs.decorations()), std::cbegin(rhs.decorations()), std::cend(rhs.decorations()), [](const MessageTestField* lhs_item, const MessageTestField* rhs_item) {return *lhs_item == *rhs_item; });
}
