#include <MessageReceiver/MessageCountingReceiver.h>

MessageCountingReceiver::MessageCountingReceiver(const MessageCountingReceiverConfiguration & config, CMSClientTestUnit & client_params, EventStatusObserver & parent)
	:MessageReceiver(config, client_params, parent),
	ReceivedMessageCounter(config.expectedEventCount())

{
}

void MessageCountingReceiver::onMessage(const cms::Message* message)
{
//	getMessaage("received message - RO DO implement parser and decorator");
	incrementReceivedCount();
	if (mListener)
		mListener->onMessage(message);
	else
		delete message;

}

