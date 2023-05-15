#pragma once
#include "MessageSender.h"
#include "..\Configuration\TestCaseDecoratingProducerConfiguration.h"
#include "..\utils\MessageDecorator.h"

class MessageDecoratingSender : public MessageSender, public MessageDecorator
{
public:
	explicit MessageDecoratingSender(const TestCaseDecoratingProducerConfiguration& config, CMSClientTestUnit & client_params, EventStatusObserver& parent);
	bool send(int msg_delay_ms = 0) override  {
	
		auto message = mSession->createTextMessage("hello msg");
		decorate(message, mSession);
		mProducer->send(message);
		return false; 
	}

private:
	long long mSentMessageCount{ 0 };
};

