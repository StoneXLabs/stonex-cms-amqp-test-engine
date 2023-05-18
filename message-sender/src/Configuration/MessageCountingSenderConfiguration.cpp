#include <Configuration/MessageCountingSenderConfiguration.h>

MessageCountingSenderConfiguration::MessageCountingSenderConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& producerId, long long message_count)
	:MessageSenderConfiguration(connectionId, sessionId,producerId),
	EventCounter(message_count)
{
}

bool operator==(const MessageCountingSenderConfiguration & lhs, const MessageCountingSenderConfiguration & rhs)
{
	return rhs.producerId() == lhs.producerId() &&
		rhs.sessionId() == lhs.sessionId() &&
		rhs.expectedEventCount() == lhs.expectedEventCount();
}
