#pragma once
#include <MessageReceiver/MessageReceiver.h>
#include "..\Configuration\FileMessageDecoratingReceiverConfiguration.h"
#include "..\utils\MessageDestination.h"
#include "..\utils\MessageVerifier.h"

class MessageDecoratingFileReceiver : public MessageReceiver, public MessageFileDestination, public MessageVerifier
{
public:
	explicit MessageDecoratingFileReceiver(const FileMessageDecoratingReceiverConfiguration& config, CMSClientTestUnit & client_params, Notifier& parent);

	void onMessage(const cms::Message* message) override;

};

