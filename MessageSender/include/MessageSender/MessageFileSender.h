#pragma once
#include <MessageSender/MessageSender.h>
#include "..\Configuration\FileTestCaseProducerConfiguration.h"
#include "..\utils\MessageSource.h"

class MessageFileSender : public MessageSender, public MessageFileSource
{
public:
	explicit MessageFileSender(const FileTestCaseProducerConfiguration& config, CMSClientTestUnit & client_params, EventStatusObserver& parent);
	bool send(int msg_delay_ms = 0) override;
};

