#include <MessageReceiver/MessageCountingFileReceiver.h>

MessageCountingFileReceiver::MessageCountingFileReceiver(const FileMessageCountingReceiverConfiguration & config, CMSClientTestUnit & client_params, EventStatusObserver & parent)
	:MessageReceiver(config, client_params,parent),
	ReceivedMessageCounter(config.expectedEventCount()),
	MessageFileDestination(config.filePath())
{
}


void MessageCountingFileReceiver::onMessage(const cms::Message* message)
{
	getMessage(message);
	incrementReceivedCount();
	if (mListener)
		mListener->onMessage(message);
	else
		delete message;

}