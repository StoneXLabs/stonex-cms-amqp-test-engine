#pragma once
class EventCounter
{
public:
	explicit EventCounter(long long expected_message_count);
	EventCounter(const EventCounter& other);
	long long expectedEventCount() const;
	friend bool operator== (const EventCounter& lhs, const EventCounter& rhs);
	
private:
	long long mExpectedEventCount{0};
};

