#pragma once
#include <MessageSender/MessageSender.h>
#include "..\Configuration\CountingCaseProducerConfiguration.h"

class MessageCountingSender : public MessageSender, public EventCounter
{
public:
	explicit MessageCountingSender(const CountingCaseProducerConfiguration& config, CMSClientTestUnit & client_params, EventStatusObserver& parent);
	bool send(int msg_delay_ms = 0) override  {return false; }

private:
	long long mSentMessageCount{ 0 };
};

