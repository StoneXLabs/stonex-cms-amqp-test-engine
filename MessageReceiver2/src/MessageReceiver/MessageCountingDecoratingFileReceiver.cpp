#include <MessageReceiver/MessageCountingDecoratingFileReceiver.h>
#include <fmt/format.h>

MessageCountingDecoratingFileReceiver::MessageCountingDecoratingFileReceiver(const FileMessageCountingDecoratingReceiverConfiguration & config, CMSClientTestUnit & client_params, Notifier & parent)
	:MessageReceiver(config, client_params),
	ReceivedMessageCounter(id(), config.expectedEventCount(), parent),
	MessageVerifier(config.consumerId(), config.decorations(), parent),
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