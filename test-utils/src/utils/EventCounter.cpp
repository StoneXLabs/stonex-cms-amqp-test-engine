#include <utils/EventCounter.h>

EventCounter::EventCounter(long long expected_message_count)
	:mExpectedEventCount{expected_message_count}
{
}

EventCounter::EventCounter(const EventCounter & other)
{
	mExpectedEventCount = other.mExpectedEventCount;
}

long long EventCounter::expectedEventCount() const
{
	return mExpectedEventCount;
}

bool operator==(const EventCounter & lhs, const EventCounter & rhs)
{
	return lhs.mExpectedEventCount == rhs.mExpectedEventCount;
}
