#include <Configuration/FileMessageReceiverConfiguration.h>

FileMessageReceiverConfiguration::FileMessageReceiverConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& consumerId, const std::string & message_file)
	:MessageReceiverConfiguration(connectionId, sessionId, consumerId),
	MessageFile(message_file)
{
}

bool operator==(const FileMessageReceiverConfiguration & lhs, const FileMessageReceiverConfiguration & rhs)
{
	return lhs.connectionId() == rhs.connectionId() &&
		lhs.sessionId() == rhs.sessionId() &&
		lhs.consumerId() == rhs.consumerId() &&
		rhs.filePath() == lhs.filePath();
}
