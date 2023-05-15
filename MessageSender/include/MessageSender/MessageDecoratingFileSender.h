#pragma once
#include <MessageSender/MessageSender.h>
#include "..\Configuration\CountingCaseProducerConfiguration.h"
#include "..\utils\MessageSource.h"
#include "..\utils\MessageDecorator.h"

class MessageDecoratingFileSender : public MessageSender, public MessageSource, public MessageDecorator
{
public:
	explicit MessageDecoratingFileSender(const CountingCaseProducerConfiguration& config, CMSClientTestUnit & client_params, EventStatusObserver& parent);
	bool send(int msg_delay_ms = 0) override  {return false; }

private:
	long long mSentMessageCount{ 0 };
};

