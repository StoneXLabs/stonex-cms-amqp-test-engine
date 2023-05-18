#pragma once
#include <MessageReceiver/MessageReceiver.h>
#include "..\Configuration\FileMessageCountingReceiverConfiguration.h"
#include "..\utils\MessageDestination.h"
#include "..\utils\ReceivedMessageCounter.h"

class MessageCountingFileReceiver : public MessageReceiver, public ReceivedMessageCounter, public MessageFileDestination
{
public:
	explicit MessageCountingFileReceiver(const FileMessageCountingReceiverConfiguration& config, CMSClientTestUnit & client_params, Notifier& parent);
	void onMessage(const cms::Message* message) override;

};

