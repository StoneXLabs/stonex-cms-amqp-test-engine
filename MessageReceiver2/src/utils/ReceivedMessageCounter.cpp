#include <utils/ReceivedMessageCounter.h>

ReceivedMessageCounter::ReceivedMessageCounter(long long expected_message_count)
	:EventCounter(expected_message_count)
{
}

long long ReceivedMessageCounter::receivedMessageCount() const
{
	return mReceivedMessagesCount;
}

void ReceivedMessageCounter::incrementReceivedCount()
{
	mReceivedMessagesCount++;
}
