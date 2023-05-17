#include <MessageReceiver/MessageFileReceiver.h>

MessageFileReceiver::MessageFileReceiver(const FileMessageReceiverConfiguration & config, CMSClientTestUnit & client_params, EventStatusObserver & parent)
	:MessageReceiver(config, client_params, parent),
	MessageFileDestination(config.filePath())
{
}


void MessageFileReceiver::onMessage(const cms::Message* message)
{
	getMessage(message);
	if (mListener)
		mListener->onMessage(message);
	else
		delete message;

}