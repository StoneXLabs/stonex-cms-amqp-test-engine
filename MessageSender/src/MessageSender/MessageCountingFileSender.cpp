#include <MessageSender/MessageCountingFileSender.h>

MessageCountingFileSender::MessageCountingFileSender(const FileCountingTestCaseProducerConfiguration & config, CMSClientTestUnit & client_params, EventStatusObserver & parent)
	:MessageSender(config, client_params,parent),
	EventCounter(config.expectedEventCount()),
	MessageFile(config.filePath())
{
}
