#include "MessageDecoratingFileSender.h"

MessageDecoratingFileSender::MessageDecoratingFileSender(const CountingCaseProducerConfiguration & config, CMSClientTestUnit & client_params, EventStatusObserver & parent)
	:MessageSender(config, client_params, parent),	
	MessageFileSource(config.filePath()) 
{
}
