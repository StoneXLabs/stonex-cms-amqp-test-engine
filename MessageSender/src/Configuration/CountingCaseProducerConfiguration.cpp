#include <Configuration/CountingCaseProducerConfiguration.h>

CountingCaseProducerConfiguration::CountingCaseProducerConfiguration(const std::string& producerId, const std::string& sessionId, long long message_count)
	:TestCaseProducerConfiguration(producerId, sessionId),
	EventCounter(message_count)
{
}

bool operator==(const CountingCaseProducerConfiguration & lhs, const CountingCaseProducerConfiguration & rhs)
{
	return rhs.producerId() == lhs.producerId() &&
		rhs.sessionId() == lhs.sessionId() &&
		rhs.expectedEventCount() == lhs.expectedEventCount();
}
