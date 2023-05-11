#include <Configuration/CountingCaseProducerConfiguration.h>

CountingCaseProducerConfiguration::CountingCaseProducerConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& producerId, long long message_count)
	:TestCaseProducerConfiguration(connectionId, sessionId,producerId),
	EventCounter(message_count)
{
}

bool operator==(const CountingCaseProducerConfiguration & lhs, const CountingCaseProducerConfiguration & rhs)
{
	return rhs.producerId() == lhs.producerId() &&
		rhs.sessionId() == lhs.sessionId() &&
		rhs.expectedEventCount() == lhs.expectedEventCount();
}
