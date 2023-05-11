#include <Configuration/FileTestCaseProducerConfiguration.h>

FileTestCaseProducerConfiguration::FileTestCaseProducerConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& producerId, const std::string & message_file)
	:TestCaseProducerConfiguration(connectionId, sessionId, producerId),
	MessageFile(message_file)
{
}

bool operator==(const FileTestCaseProducerConfiguration & lhs, const FileTestCaseProducerConfiguration & rhs)
{
	return lhs.connectionId() == rhs.connectionId() &&
		lhs.sessionId() == rhs.sessionId() &&
		lhs.producerId() == rhs.producerId() &&
		rhs.filePath() == lhs.filePath();
}
