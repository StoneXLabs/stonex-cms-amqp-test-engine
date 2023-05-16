#pragma once

#include <MessageSender/MessageSender.h>
#include "..\Configuration\FileMessageCountingDecoratingSenderConfiguration.h"
#include "..\utils\SentMessageCounter.h"
#include "..\utils\MessageSource.h"
#include "..\utils\MessageDecorator.h"

class MessageCountingDecoratingFileSender : public MessageSender, public SentMessageCounter, public MessageDecorator, public MessageFileSource
{
public:
	explicit MessageCountingDecoratingFileSender(const FileMessageCountingDecoratingSenderConfiguration& config, CMSClientTestUnit & client_params, EventStatusObserver& parent);

	bool send(int msg_delay_ms = 0) override;
	std::string createMessageBody() override;
};

