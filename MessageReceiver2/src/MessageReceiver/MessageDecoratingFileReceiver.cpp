#include <MessageReceiver/MessageDecoratingFileReceiver.h>



MessageDecoratingFileReceiver::MessageDecoratingFileReceiver(const FileMessageDecoratingReceiverConfiguration & config, CMSClientTestUnit & client_params, Notifier & parent)
	: MessageReceiver(config, client_params),
	MessageFileDestination(config.filePath()),
	MessageVerifier(config.consumerId(), config.decorations(), parent)

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