#include <MessageReceiver/MessageCountingDecoratingReceiver.h>
#include <fmt/format.h>

MessageCountingDecoratingReceiver::MessageCountingDecoratingReceiver(const MessageCountingDecoratingReceiverConfiguration & config, CMSClientTestUnit & client_params, Notifier & parent)
	:MessageReceiver(config,client_params),
	ReceivedMessageCounter(id(), config.expectedEventCount(), parent),
	MessageVerifier(config.consumerId(), config.decorations(), parent)
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