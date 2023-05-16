#include <MessageSender/MessageCountingFileSender.h>

MessageCountingFileSender::MessageCountingFileSender(const FileMessageCountingSenderConfiguration & config, CMSClientTestUnit & client_params, EventStatusObserver & parent)
	:MessageSender(config, client_params,parent),
	SentMessageCounter(config.expectedEventCount()),
	MessageFileSource(config.filePath())
{
}

bool MessageCountingFileSender::send(int msg_delay_ms)
{
	auto message_body = createMessageBody();
	if (message_body.empty())
		return false;


	if (mSession && mProducer)
	{
		auto message = mSession->createTextMessage(message_body);
		mProducer->send(message);
		incrementSentCount();
		return false;
	}
	return false;

}

std::string MessageCountingFileSender::createMessageBody()
{
	return getMessage();
}

