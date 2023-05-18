#pragma once
#include <MessageSender/MessageSender.h>
#include "..\Configuration\FileMessageCountingSenderConfiguration.h"
#include "..\utils\MessageSource.h"
#include "..\utils\SentMessageCounter.h"

class MessageCountingFileSender : public MessageSender, public SentMessageCounter, public MessageFileSource
{
public:
	explicit MessageCountingFileSender(const FileMessageCountingSenderConfiguration& config, CMSClientTestUnit & client_params, Notifier& parent);
	bool send(int msg_delay_ms = 0) override;
	std::string createMessageBody() override;
};

