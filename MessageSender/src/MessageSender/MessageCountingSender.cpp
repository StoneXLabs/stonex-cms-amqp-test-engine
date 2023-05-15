#include <MessageSender/MessageCountingSender.h>

MessageCountingSender::MessageCountingSender(const CountingCaseProducerConfiguration & config, CMSClientTestUnit & client_params, EventStatusObserver & parent)
	:MessageSender(config, client_params, parent),
	SentMessageCounter(config.expectedEventCount())

{
}

bool MessageCountingSender::send(int msg_delay_ms)
{
	if (mSession && mProducer)
	{
		auto mes = mSession->createTextMessage("dummy message");
		mProducer->send(mes);
		incrementSentCount();
		return true;
	}
	return false;

}
}
