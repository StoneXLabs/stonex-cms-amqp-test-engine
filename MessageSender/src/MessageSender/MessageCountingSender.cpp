#include <MessageSender/MessageCountingSender.h>

MessageCountingSender::MessageCountingSender(const MessageCountingSenderConfiguration & config, CMSClientTestUnit & client_params, Notifier & parent)
	:MessageSender(config, client_params, parent),
	SentMessageCounter(config.expectedEventCount())

{
}

bool MessageCountingSender::send(int msg_delay_ms)
{

	auto message_body = createMessageBody();
	if (message_body.empty())
		return false;

	if (mSession && mProducer)
	{
		auto mes = mSession->createTextMessage(message_body);
		mProducer->send(mes);
		incrementSentCount();
		return true;
	}
	else
		return false;

}

