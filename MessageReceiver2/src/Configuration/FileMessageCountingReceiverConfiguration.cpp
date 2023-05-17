#include <Configuration/FileMessageCountingReceiverConfiguration.h>




FileMessageCountingReceiverConfiguration::FileMessageCountingReceiverConfiguration(const std::string & connectionId, const std::string & sessionId, const std::string & consumerId, const std::string & messageFile, long long message_count)
	:MessageReceiverConfiguration(connectionId, sessionId, consumerId),
	EventCounter(message_count),
	MessageFile(messageFile)
{
}

bool operator==(const FileMessageCountingReceiverConfiguration & lhs, const FileMessageCountingReceiverConfiguration & rhs)
{
	return lhs.connectionId() == rhs.connectionId() &&
		lhs.sessionId() == rhs.sessionId() &&
		lhs.consumerId() == rhs.consumerId() &&
		rhs.expectedEventCount() == lhs.expectedEventCount() &&
		rhs.filePath() == lhs.filePath();
}