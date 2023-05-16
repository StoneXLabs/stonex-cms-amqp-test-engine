#include <MessageSender/MessageFileSender.h>

MessageFileSender::MessageFileSender(const FileMessageSenderConfiguration & config, CMSClientTestUnit & client_params, EventStatusObserver & parent)
	:MessageSender(config, client_params, parent),
	MessageFileSource(config.filePath())
{
}

bool MessageFileSender::send(int msg_delay_ms)
{
	auto message_body = createMessageBody();
	if (message_body.empty())
		return false;

	if (mSession && mProducer)
	{
		auto mes = mSession->createTextMessage(message_body);
		mProducer->send(mes);
		return true;
	}
	return false;

}

std::string MessageFileSender::createMessageBody()
{
	return getMessage();
}
