#include <utils/MessageDecorator.h>
#include <MessageDecorator/MessageDecoratorFactory.h>

MessageDecorator::MessageDecorator(const MessageDecoratorConfiguration & decoratorConfig)
{
	MessageDecoratorFactory decorator_factory;
	mDecorator = decorator_factory.create(decoratorConfig);
}

void MessageDecorator::decorate(cms::Message* message, cms::Session* session) const
{
	mDecorator->decorate(message, session);
}
