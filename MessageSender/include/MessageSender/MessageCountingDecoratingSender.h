#pragma once
#include <MessageSender/MessageSender.h>
#include "..\Configuration\MessageCountingDecoratingSenderConfiguration.h"
#include "..\utils\SentMessageCounter.h"
#include "..\utils\MessageDecorator.h"

class MessageCountingDecoratingSender : public MessageSender, public SentMessageCounter,public MessageDecorator
{
public:
	explicit MessageCountingDecoratingSender(const MessageCountingDecoratingSenderConfiguration& config, CMSClientTestUnit & client_params, EventStatusObserver& parent);
	bool send(int msg_delay_ms = 0) override;

};

