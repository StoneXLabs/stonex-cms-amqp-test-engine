#pragma once
#include <utils/EventCounter.h>
#include <string>
#include <Notifier/TestNotifier.h>

class ReceivedMessageCounter : public EventCounter
{
public:
	ReceivedMessageCounter(const std::string &id, long long expected_message_count, Notifier & parent);
	~ReceivedMessageCounter();
	long long receivedMessageCount() const;
	void incrementReceivedCount();
private:
	long long mReceivedMessagesCount{ 0 };
	const std::string mId;
	Notifier &mParent;

};

