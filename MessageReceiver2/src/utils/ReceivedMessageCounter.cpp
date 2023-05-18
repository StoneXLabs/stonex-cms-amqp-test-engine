#include <utils/ReceivedMessageCounter.h>
#include <Notifier/TestNotifier.h>
#include <fmt/format.h>

ReceivedMessageCounter::ReceivedMessageCounter(const std::string &id, long long expected_message_count, Notifier & parent)
	:EventCounter(expected_message_count),
	mParent{ parent },
	mId{id}
{
}

ReceivedMessageCounter::~ReceivedMessageCounter()
{
	if (expectedEventCount() == mReceivedMessagesCount)
		mParent.testEvent(EventStatus(true, mId, fmt::format("expected message count reached [{}/{}]", receivedMessageCount(), expectedEventCount())));

}

long long ReceivedMessageCounter::receivedMessageCount() const
{
	return mReceivedMessagesCount;
}

void ReceivedMessageCounter::incrementReceivedCount()
{
	mReceivedMessagesCount++;
	if (expectedEventCount() > mReceivedMessagesCount)
		mParent.testEvent(EventStatus(false, mId, fmt::format("expected message count exceeded [{}/{}]", receivedMessageCount(), expectedEventCount())));
}
