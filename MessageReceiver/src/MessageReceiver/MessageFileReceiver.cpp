#include <MessageReceiver/MessageFileReceiver.h>

MessageFileReceiver::MessageFileReceiver(const FileMessageReceiverConfiguration & config, CMSClientTestUnit & client_params, Notifier & parent)
	:MessageReceiver(config, client_params),
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