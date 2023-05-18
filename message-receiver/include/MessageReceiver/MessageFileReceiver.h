#pragma once
#include <MessageReceiver/MessageReceiver.h>
#include "..\Configuration\FileMessageReceiverConfiguration.h"
#include "..\utils\MessageDestination.h"

class MessageFileReceiver : public MessageReceiver, public MessageFileDestination
{
public:
	explicit MessageFileReceiver(const FileMessageReceiverConfiguration& config, CMSClientTestUnit & client_params, Notifier& parent);

	void onMessage(const cms::Message* message) override;
};

