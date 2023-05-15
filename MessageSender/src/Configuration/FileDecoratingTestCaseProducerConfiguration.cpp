#include <Configuration\FileDecoratingTestCaseProducerConfiguration.h>

FileDecoratingTestCaseProducerConfiguration::FileDecoratingTestCaseProducerConfiguration(const std::string & connectionId, const std::string & sessionId, const std::string & producerId, const std::string & message_file, const std::vector<MessageTestField*>& decorations)
	:TestCaseProducerConfiguration(connectionId, sessionId, producerId),
	MessageFile(message_file),
	MessageDecoratorConfiguration(decorations)
{
}

bool operator==(const FileDecoratingTestCaseProducerConfiguration & lhs, const FileDecoratingTestCaseProducerConfiguration & rhs)
{
	return lhs.connectionId() == rhs.connectionId() &&
		lhs.sessionId() == rhs.sessionId() &&
		lhs.producerId() == rhs.producerId() &&
		rhs.filePath() == lhs.filePath() &&
		std::equal(std::cbegin(lhs.decorations()), std::cend(lhs.decorations()), std::cbegin(rhs.decorations()), std::cend(rhs.decorations()), [](const MessageTestField* lhs_item, const MessageTestField* rhs_item) {return *lhs_item == *rhs_item; });

}
