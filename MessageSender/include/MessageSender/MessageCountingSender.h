#pragma once
#include <MessageSender/MessageSender.h>
#include "..\Configuration\CountingCaseProducerConfiguration.h"
#include "..\utils\SentMessageCounter.h"

class MessageCountingSender : public MessageSender, public SentMessageCounter
{
public:
	explicit MessageCountingSender(const CountingCaseProducerConfiguration& config, CMSClientTestUnit & client_params, EventStatusObserver& parent);
	bool send(int msg_delay_ms = 0) override;

};

