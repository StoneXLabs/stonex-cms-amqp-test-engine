#include <Configuration/FileCountingTestCaseProducerConfiguration.h>

FileCountingTestCaseProducerConfiguration::FileCountingTestCaseProducerConfiguration(const std::string& producerId, const std::string& sessionId, const std::string& file_path, long long message_count)
	:TestCaseProducerConfiguration(producerId, sessionId),
	MessageFile(file_path),
	EventCounter(message_count)
{
}

bool operator==(const FileCountingTestCaseProducerConfiguration & lhs, const FileCountingTestCaseProducerConfiguration & rhs)
{
	return rhs.producerId() == lhs.producerId() &&
		rhs.sessionId() == lhs.sessionId() &&
		rhs.expectedEventCount() == lhs.expectedEventCount() &&
		rhs.filePath() == lhs.filePath();
}
