#include <MessageReceiver/MessageDecoratingReceiver.h>
#include <MessageDecorator/MessageDecoratorFactory.h>

MessageDecoratingReceiver::MessageDecoratingReceiver(const MessageDecoratingReceiverConfiguration & config, CMSClientTestUnit & client_params, Notifier & parent)
	:MessageReceiver(config, client_params),
	MessageVerifier(config.consumerId(),config.decorations(),parent)
{
}


void MessageDecoratingReceiver::onMessage(const cms::Message* message)
{
	std::cout<<"received message - RO DO implement parser and decorator"<<std::endl;
	verify(message);
	if (mListener)
		mListener->onMessage(message);
	else
		delete message;

}