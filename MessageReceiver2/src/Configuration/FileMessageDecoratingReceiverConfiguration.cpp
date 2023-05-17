#include <Configuration\FileMessageDecoratingReceiverConfiguration.h>

FileMessageDecoratingReceiverConfiguration::FileMessageDecoratingReceiverConfiguration(const std::string & connectionId, const std::string & sessionId, const std::string & consumerId, const std::string & message_file, const std::vector<MessageTestField*>& decorations)
	:MessageReceiverConfiguration(connectionId, sessionId, consumerId),
	MessageFile(message_file),
	MessageDecoratorConfiguration(decorations)
{
}

bool operator==(const FileMessageDecoratingReceiverConfiguration & lhs, const FileMessageDecoratingReceiverConfiguration & rhs)
{
	return lhs.connectionId() == rhs.connectionId() &&
		lhs.sessionId() == rhs.sessionId() &&
		lhs.consumerId() == rhs.consumerId() &&
		rhs.filePath() == lhs.filePath() &&
		std::equal(std::cbegin(lhs.decorations()), std::cend(lhs.decorations()), std::cbegin(rhs.decorations()), std::cend(rhs.decorations()), [](const MessageTestField* lhs_item, const MessageTestField* rhs_item) {return *lhs_item == *rhs_item; });

}
