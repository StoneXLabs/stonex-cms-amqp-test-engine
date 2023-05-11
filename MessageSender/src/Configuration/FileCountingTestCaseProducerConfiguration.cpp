#include <Configuration/FileCountingTestCaseProducerConfiguration.h>

FileCountingTestCaseProducerConfiguration::FileCountingTestCaseProducerConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& producerId, const std::string& file_path, long long message_count)
	:TestCaseProducerConfiguration(connectionId, sessionId, producerId),
	MessageFile(file_path),
	EventCounter(message_count)
{
}

bool operator==(const FileCountingTestCaseProducerConfiguration & lhs, const FileCountingTestCaseProducerConfiguration & rhs)
{
	return lhs.connectionId() == rhs.connectionId() &&
		lhs.sessionId() == rhs.sessionId() &&
		lhs.producerId() == rhs.producerId() &&
		rhs.expectedEventCount() == lhs.expectedEventCount() &&
		rhs.filePath() == lhs.filePath();
}
