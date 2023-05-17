#pragma once
#include <MessageReceiver/MessageReceiver.h>
#include "..\Configuration\MessageCountingReceiverConfiguration.h"
#include "..\utils\ReceivedMessageCounter.h"

class MessageCountingReceiver : public MessageReceiver, public ReceivedMessageCounter
{
public:
	explicit MessageCountingReceiver(const MessageCountingReceiverConfiguration& config, CMSClientTestUnit & client_params, EventStatusObserver& parent);

	void onMessage(const cms::Message* message) override;

};

