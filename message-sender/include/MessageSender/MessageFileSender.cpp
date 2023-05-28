#include "MessageFileSender.h"

MessageFileSender::MessageFileSender(const FileTestCaseProducerConfiguration & config, CMSClientTestUnit & client_params, EventStatusObserver & parent)
	:MessageSender(config, client_params, parent),
	MessageFile(config.filePath())
{
}
