#pragma once

#include <MessageReceiver/MessageReceiver.h>
#include "..\Configuration\FileMessageCountingDecoratingReceiverConfiguration.h"
#include "..\utils\ReceivedMessageCounter.h"
#include "..\utils\MessageDestination.h"
#include "..\utils\MessageVerifier.h"

class MessageCountingDecoratingFileReceiver : public MessageReceiver, public ReceivedMessageCounter, public MessageVerifier, public MessageFileDestination
{
public:
	explicit MessageCountingDecoratingFileReceiver(const FileMessageCountingDecoratingReceiverConfiguration& config, CMSClientTestUnit & client_params, EventStatusObserver& parent);
	void onMessage(const cms::Message* message) override;

};

