#pragma once
#include <MessageSender/MessageSender.h>
#include "..\Configuration\FileCountingTestCaseProducerConfiguration.h"
#include "..\utils\MessageSource.h"
#include "..\utils\SentMessageCounter.h"

class MessageCountingFileSender : public MessageSender, public SentMessageCounter, public MessageFileSource
{
public:
	explicit MessageCountingFileSender(const FileCountingTestCaseProducerConfiguration& config, CMSClientTestUnit & client_params, EventStatusObserver& parent);
	bool send(int msg_delay_ms = 0);
};

