#include <MessageSender/MessageDecoratingFileSender.h>



MessageDecoratingFileSender::MessageDecoratingFileSender(const FileMessageDecoratingSenderConfiguration & config, CMSClientTestUnit & client_params, EventStatusObserver & parent)
	: MessageSender(config, client_params, parent),
	MessageFileSource(config.filePath()),
	MessageDecorator(config.decorations())
{
}

bool MessageDecoratingFileSender::send(int msg_delay_ms)
{
	auto message_body = createMessageBody();
	if (message_body.empty())
		return false;


	if (mSession && mProducer)
	{
		auto message = mSession->createTextMessage(message_body);
		decorate(message, mSession);
		mProducer->send(message);
		return false;
	}
	return false;
}

std::string MessageDecoratingFileSender::createMessageBody()
{
	return getMessage();
}
