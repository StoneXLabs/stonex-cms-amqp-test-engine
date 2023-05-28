#include "MessageDecoratingSender.h"
#include <MessageDecorator/MessageDecoratorFactory.h>

MessageDecoratingSender::MessageDecoratingSender(const TestCaseDecoratingProducerConfiguration & config, CMSClientTestUnit & client_params, EventStatusObserver & parent)
	:MessageSender(config, client_params, parent),
	MessageDecorator(config.decorations())
{
}
