#pragma once
#include <MessageSender/MessageSender.h>
#include "..\Configuration\CountingCaseProducerConfiguration.h"
#include "..\Configuration\MessageFile.h"

class MessageCountingDecoratingSender : public MessageSender, public EventCounter
{
public:
	explicit MessageCountingDecoratingSender(const CountingCaseProducerConfiguration& config, CMSClientTestUnit & client_params, EventStatusObserver& parent);
	bool send(int msg_delay_ms = 0) override  {return false; }

private:
	long long mSentMessageCount{ 0 };
};

