#pragma once
#include <MessageReceiver/MessageReceiver.h>
#include "..\Configuration\MessageCountingDecoratingReceiverConfiguration.h"
#include "..\utils\ReceivedMessageCounter.h"
#include "..\utils\MessageVerifier.h"

class MessageCountingDecoratingReceiver : public MessageReceiver, public ReceivedMessageCounter,public MessageVerifier
{
public:
	explicit MessageCountingDecoratingReceiver(const MessageCountingDecoratingReceiverConfiguration& config, CMSClientTestUnit & client_params, Notifier& parent);
	void onMessage(const cms::Message* message) override;


};

