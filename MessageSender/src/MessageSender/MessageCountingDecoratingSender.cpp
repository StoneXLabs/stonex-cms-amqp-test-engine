#include <MessageSender/MessageCountingDecoratingSender.h>

MessageCountingDecoratingSender::MessageCountingDecoratingSender(const MessageCountingDecoratingSenderConfiguration & config, CMSClientTestUnit & client_params, EventStatusObserver & parent)
	:MessageSender(config,client_params,parent),
	SentMessageCounter(config.expectedEventCount()),
	MessageDecorator(config.decorations())
{
}

bool MessageCountingDecoratingSender::send(int msg_delay_ms) 
{

	auto message_body = createMessageBody();
	if (message_body.empty())
		return false;


	if (mSession && mProducer)
	{
		auto message = mSession->createTextMessage(message_body);
		decorate(message, mSession);
		mProducer->send(message);
		incrementSentCount();
		return false;
	}
	return false;
}

