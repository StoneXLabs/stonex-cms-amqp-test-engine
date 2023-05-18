#include <Configuration/FileMessageCountingSenderConfiguration.h>




FileMessageCountingSenderConfiguration::FileMessageCountingSenderConfiguration(const std::string & connectionId, const std::string & sessionId, const std::string & producerId, const std::string & messageFile, long long message_count)
	:MessageSenderConfiguration(connectionId, sessionId, producerId),
	EventCounter(message_count),
	MessageFile(messageFile)
{
}

bool operator==(const FileMessageCountingSenderConfiguration & lhs, const FileMessageCountingSenderConfiguration & rhs)
{
	return lhs.connectionId() == rhs.connectionId() &&
		lhs.sessionId() == rhs.sessionId() &&
		lhs.producerId() == rhs.producerId() &&
		rhs.expectedEventCount() == lhs.expectedEventCount() &&
		rhs.filePath() == lhs.filePath();
}