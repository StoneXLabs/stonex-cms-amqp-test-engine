#include <utils/SentMessageCounter.h>

SentMessageCounter::SentMessageCounter(long long expected_message_count)
	:EventCounter(expected_message_count)
{
}

long long SentMessageCounter::sentMessageCount() const
{
	return mSentMessagesCount;
}

void SentMessageCounter::incrementSentCount()
{
	mSentMessagesCount++;
}
