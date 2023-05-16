#pragma once
#include <MessageSender/MessageSender.h>
#include "..\Configuration\FileMessageDecoratingSenderConfiguration.h"
#include "..\utils\MessageSource.h"
#include "..\utils\MessageDecorator.h"

class MessageDecoratingFileSender : public MessageSender, public MessageFileSource, public MessageDecorator
{
public:
	explicit MessageDecoratingFileSender(const FileMessageDecoratingSenderConfiguration& config, CMSClientTestUnit & client_params, EventStatusObserver& parent);
	bool send(int msg_delay_ms = 0) override;
	std::string createMessageBody() override;

};

