#include <MessageReceiver/MessageCountingFileReceiver.h>

MessageCountingFileReceiver::MessageCountingFileReceiver(const FileMessageCountingReceiverConfiguration & config, CMSClientTestUnit & client_params, Notifier & parent)
	:MessageReceiver(config, client_params),
	ReceivedMessageCounter(id(), config.expectedEventCount(), parent),
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