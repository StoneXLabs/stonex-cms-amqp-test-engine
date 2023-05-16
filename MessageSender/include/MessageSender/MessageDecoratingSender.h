#pragma once
#include "MessageSender.h"
#include "..\Configuration\MessageDecoratingSenderConfiguration.h"
#include "..\utils\MessageDecorator.h"

class MessageDecoratingSender : public MessageSender, public MessageDecorator
{
public:
	explicit MessageDecoratingSender(const MessageDecoratingSenderConfiguration& config, CMSClientTestUnit & client_params, EventStatusObserver& parent);
	bool send(int msg_delay_ms = 0) override;


};

