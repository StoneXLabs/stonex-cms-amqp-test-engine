#pragma once
#include <MessageSender/MessageSender.h>
#include "..\Configuration\CountingCaseProducerConfiguration.h"
#include "..\utils\SentMessageCounter.h"
#include "..\Configuration\MessageFile.h"
#include "..\utils\MessageDecorator.h"

class MessageCountingDecoratingSender : public MessageSender, public SentMessageCounter, MessageDecorator
{
public:
	explicit MessageCountingDecoratingSender(const CountingCaseProducerConfiguration& config, CMSClientTestUnit & client_params, EventStatusObserver& parent);
	bool send(int msg_delay_ms = 0) override  {return false; }

};

