#include <Configuration/FileMessageSenderConfiguration.h>

FileMessageSenderConfiguration::FileMessageSenderConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& producerId, const std::string & message_file)
	:MessageSenderConfiguration(connectionId, sessionId, producerId),
	MessageFile(message_file)
{
}

bool operator==(const FileMessageSenderConfiguration & lhs, const FileMessageSenderConfiguration & rhs)
{
	return lhs.connectionId() == rhs.connectionId() &&
		lhs.sessionId() == rhs.sessionId() &&
		lhs.producerId() == rhs.producerId() &&
		rhs.filePath() == lhs.filePath();
}
