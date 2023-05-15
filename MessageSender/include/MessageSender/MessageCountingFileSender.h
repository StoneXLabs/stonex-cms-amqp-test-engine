#pragma once
#include <MessageSender/MessageSender.h>
#include "..\Configuration\FileCountingTestCaseProducerConfiguration.h"

class MessageCountingFileSender : public MessageSender, public EventCounter, public MessageFile
{
public:
	explicit MessageCountingFileSender(const FileCountingTestCaseProducerConfiguration& config, CMSClientTestUnit & client_params, EventStatusObserver& parent);
	bool send(int msg_delay_ms = 0) override  {return false; }

private:
	long long mSentMessageCount{ 0 };
};

