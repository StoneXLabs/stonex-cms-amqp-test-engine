#pragma once
#include "../Configuration/EventCounter.h"

class SentMessageCounter : public EventCounter
{
public:
	SentMessageCounter(long long expected_message_count);
	long long sentMessageCount() const;
	void incrementSentCount();
private:
	long long mSentMessagesCount{ 0 };
};

