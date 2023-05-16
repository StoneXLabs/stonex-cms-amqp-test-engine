#include <MessageSender/MessageDecoratingSender.h>
#include <MessageDecorator/MessageDecoratorFactory.h>

MessageDecoratingSender::MessageDecoratingSender(const MessageDecoratingSenderConfiguration & config, CMSClientTestUnit & client_params, EventStatusObserver & parent)
	:MessageSender(config, client_params, parent),
	MessageDecorator(config.decorations())
{
}

bool MessageDecoratingSender::send(int msg_delay_ms)
{
	auto message_body = createMessageBody();
	if (message_body.empty())
		return false;


	if (mSession && mProducer)
	{
		auto message = mSession->createTextMessage(message_body);
		decorate(message, mSession);
		mProducer->send(message);
		return false;
	}
	return false;

}

