#include <Configuration/FileTestCaseProducerConfiguration.h>

FileTestCaseProducerConfiguration::FileTestCaseProducerConfiguration(const std::string& producerId, const std::string& sessionId, const std::string & message_file)
	:TestCaseProducerConfiguration(producerId, sessionId),
	MessageFile(message_file)
{
}

bool operator==(const FileTestCaseProducerConfiguration & lhs, const FileTestCaseProducerConfiguration & rhs)
{
	return rhs.producerId() == lhs.producerId() &&
		rhs.sessionId() == lhs.sessionId() &&
		rhs.filePath() == lhs.filePath();
}
