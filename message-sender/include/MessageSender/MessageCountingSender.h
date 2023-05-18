#pragma once
#include <MessageSender/MessageSender.h>
#include "..\Configuration\MessageCountingSenderConfiguration.h"
#include "..\utils\SentMessageCounter.h"

class MessageCountingSender : public MessageSender, public SentMessageCounter
{
public:
	explicit MessageCountingSender(const MessageCountingSenderConfiguration& config, CMSClientTestUnit & client_params, Notifier& parent);
	bool send(int msg_delay_ms = 0) override;

};

