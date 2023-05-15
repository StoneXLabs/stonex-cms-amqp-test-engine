#include <Configuration/TestCaseDecoratingProducerConfiguration.h>

TestCaseDecoratingProducerConfiguration::TestCaseDecoratingProducerConfiguration(const std::string & connectionId, const std::string & sessionId, const std::string & producerId, const std::vector<MessageTestField*>& decorations)
	:TestCaseProducerConfiguration(connectionId, sessionId, producerId),
	MessageDecoratorConfiguration(decorations)
{
}

bool operator==(const TestCaseDecoratingProducerConfiguration & lhs, const TestCaseDecoratingProducerConfiguration & rhs)
{
	return lhs.connectionId() == rhs.connectionId() &&
		lhs.sessionId() == rhs.sessionId() &&
		lhs.producerId() == rhs.producerId() &&
		std::equal(std::cbegin(lhs.decorations()), std::cend(lhs.decorations()), std::cbegin(rhs.decorations()), std::cend(rhs.decorations()), [](const MessageTestField* lhs_item, const MessageTestField* rhs_item) {return *lhs_item == *rhs_item; });
}
