#pragma once
#include "MessageReceiver.h"
#include "..\Configuration\MessageDecoratingReceiverConfiguration.h"
#include "..\utils\MessageVerifier.h"

class MessageDecoratingReceiver : public MessageReceiver, public MessageVerifier
{
public:
	explicit MessageDecoratingReceiver(const MessageDecoratingReceiverConfiguration& config, CMSClientTestUnit & client_params, EventStatusObserver& parent);

	void onMessage(const cms::Message* message) override;


};

