#include <Configuration/FileMessageCountingSenderDecoratingConfiguration.h>

FileMessageCountingSenderDecoratingConfiguration::FileMessageCountingSenderDecoratingConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& producerId, const std::string& messageType, const std::string& senderType, const std::string& message_file, const std::string& file_path, long long message_count)
	:MessageSenderConfiguration(connectionId, sessionId, producerId, messageType, senderType),
	MessageFile(file_path),
	EventCounter(message_count)
{
}

bool operator==(const FileMessageCountingSenderDecoratingConfiguration& lhs, const FileMessageCountingSenderDecoratingConfiguration& rhs)
{
	return lhs.connectionId() == rhs.connectionId() &&
		lhs.sessionId() == rhs.sessionId() &&
		lhs.producerId() == rhs.producerId() &&
		rhs.expectedEventCount() == lhs.expectedEventCount() &&
		rhs.filePath() == lhs.filePath();
}
