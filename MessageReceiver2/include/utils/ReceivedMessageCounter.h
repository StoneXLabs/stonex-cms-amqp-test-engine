#pragma once
#include <utils/EventCounter.h>

class ReceivedMessageCounter : public EventCounter
{
public:
	ReceivedMessageCounter(long long expected_message_count);
	long long receivedMessageCount() const;
	void incrementReceivedCount();
private:
	long long mReceivedMessagesCount{ 0 };
};

