#include <MessageSender/MessageCountingSender.h>

MessageCountingSender::MessageCountingSender(const CountingCaseProducerConfiguration & config, CMSClientTestUnit & client_params, EventStatusObserver & parent)
	:MessageSender(config, client_params, parent),
	EventCounter(config.expectedEventCount())

{
}
