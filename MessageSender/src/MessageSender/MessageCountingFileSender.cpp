#include <MessageSender/MessageCountingFileSender.h>

MessageCountingFileSender::MessageCountingFileSender(const FileCountingTestCaseProducerConfiguration & config, CMSClientTestUnit & client_params, EventStatusObserver & parent)
	:MessageSender(config, client_params,parent),
	SentMessageCounter(config.expectedEventCount()),
	MessageFileSource(config.filePath())
{
}

bool MessageCountingFileSender::send(int msg_delay_ms)
{
	auto message_body = getMessage();
	if (message_body.empty())
		return false;

	if (mSession && mProducer)
	{
		auto mes = mSession->createTextMessage(message_body);
		mProducer->send(mes);
		incrementSentCount();
		return true;
	}
	return false;

}
}
