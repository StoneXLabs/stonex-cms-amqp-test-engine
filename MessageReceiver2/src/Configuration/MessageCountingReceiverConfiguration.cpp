#include <Configuration/MessageCountingReceiverConfiguration.h>

MessageCountingReceiverConfiguration::MessageCountingReceiverConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& consumerId, long long message_count)
	:MessageReceiverConfiguration(connectionId, sessionId,consumerId),
	EventCounter(message_count)
{
}

bool operator==(const MessageCountingReceiverConfiguration & lhs, const MessageCountingReceiverConfiguration & rhs)
{
	return rhs.consumerId() == lhs.consumerId() &&
		rhs.sessionId() == lhs.sessionId() &&
		rhs.expectedEventCount() == lhs.expectedEventCount();
}
