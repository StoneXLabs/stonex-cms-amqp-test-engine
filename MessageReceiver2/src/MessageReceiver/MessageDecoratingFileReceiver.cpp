#include <MessageReceiver/MessageDecoratingFileReceiver.h>



MessageDecoratingFileReceiver::MessageDecoratingFileReceiver(const FileMessageDecoratingReceiverConfiguration & config, CMSClientTestUnit & client_params, EventStatusObserver & parent)
	: MessageReceiver(config, client_params, parent),
	MessageFileDestination(config.filePath()),
	MessageVerifier(config.decorations())
{
}

void MessageDecoratingFileReceiver::onMessage(const cms::Message* message)
{
	getMessage(message);
	if (mListener)
		mListener->onMessage(message);
	else
		delete message;

}