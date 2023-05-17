#include <MessageReceiver/MessageDecoratingReceiver.h>
#include <MessageDecorator/MessageDecoratorFactory.h>

MessageDecoratingReceiver::MessageDecoratingReceiver(const MessageDecoratingReceiverConfiguration & config, CMSClientTestUnit & client_params, EventStatusObserver & parent)
	:MessageReceiver(config, client_params, parent),
	MessageVerifier(config.decorations())
{
}


void MessageDecoratingReceiver::onMessage(const cms::Message* message)
{
	std::cout<<"received message - RO DO implement parser and decorator"<<std::endl;
	if (mListener)
		mListener->onMessage(message);
	else
		delete message;

}