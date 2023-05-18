#include <Configuration/FileMessageCountingDecoratingSenderConfiguration.h>

FileMessageCountingDecoratingSenderConfiguration::FileMessageCountingDecoratingSenderConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& producerId, const std::string& file_path, long long message_count, const std::vector<MessageTestField*>& decorations)
	:MessageSenderConfiguration(connectionId, sessionId, producerId),
	MessageFile(file_path),
	EventCounter(message_count),
	MessageDecoratorConfiguration(decorations)
{
}

bool operator==(const FileMessageCountingDecoratingSenderConfiguration & lhs, const FileMessageCountingDecoratingSenderConfiguration & rhs)
{
	return lhs.connectionId() == rhs.connectionId() &&
		lhs.sessionId() == rhs.sessionId() &&
		lhs.producerId() == rhs.producerId() &&
		rhs.expectedEventCount() == lhs.expectedEventCount() &&
		rhs.filePath() == lhs.filePath() &&
		std::equal(std::cbegin(lhs.decorations()), std::cend(lhs.decorations()), std::cbegin(rhs.decorations()), std::cend(rhs.decorations()), [](const MessageTestField* lhs_item, const MessageTestField* rhs_item) {return *lhs_item == *rhs_item; });

}
