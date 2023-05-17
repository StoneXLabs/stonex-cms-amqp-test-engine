#include <MessageReceiver/MessageCountingDecoratingReceiver.h>

MessageCountingDecoratingReceiver::MessageCountingDecoratingReceiver(const MessageCountingDecoratingReceiverConfiguration & config, CMSClientTestUnit & client_params, EventStatusObserver & parent)
	:MessageReceiver(config,client_params,parent),
	ReceivedMessageCounter(config.expectedEventCount()),
	MessageVerifier(config.decorations())
{
}

void MessageCountingDecoratingReceiver::onMessage(const cms::Message* message)
{
	std::cout<<"received message - RO DO implement parser and verifier"<<std::endl;
	incrementReceivedCount();
	if (mListener)
		mListener->onMessage(message);
	else
		delete message;

}