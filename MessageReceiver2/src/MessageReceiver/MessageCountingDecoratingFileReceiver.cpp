#include <MessageReceiver/MessageCountingDecoratingFileReceiver.h>

MessageCountingDecoratingFileReceiver::MessageCountingDecoratingFileReceiver(const FileMessageCountingDecoratingReceiverConfiguration & config, CMSClientTestUnit & client_params, EventStatusObserver & parent)
	:MessageReceiver(config, client_params, parent),
	ReceivedMessageCounter(config.expectedEventCount()),
	MessageVerifier(config.decorations()),
	MessageFileDestination(config.filePath())
{
}


void MessageCountingDecoratingFileReceiver::onMessage(const cms::Message* message)
{
	getMessage(message);
	verify(message);
	incrementReceivedCount();
	if (mListener)
		mListener->onMessage(message);
	else
		delete message;

}