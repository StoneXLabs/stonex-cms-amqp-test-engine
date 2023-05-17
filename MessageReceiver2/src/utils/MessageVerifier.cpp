#include <utils/MessageVerifier.h>
#include <MessageDecorator/MessageDecoratorFactory.h>
#include <TestEventWrapperFactory/EventWrapperFactory.h>

MessageVerifier::MessageVerifier(const MessageDecoratorConfiguration & decoratorConfig)
{
	

	std::transform(std::cbegin(decoratorConfig.decorations()), std::cend(decoratorConfig.decorations()), std::back_inserter(mVerifiers), 
		[this](MessageTestField* item) {
		return mVerifierFactory.create(item->type(), true, false, item->valueString(), item->name());
	});

}

void MessageVerifier::verify(const cms::Message* message) const
{
	

	std::for_each(std::cbegin(mVerifiers), std::end(mVerifiers), [this, message](IExpectedField* item)
	{
		auto t = mVerifierFactory.create(message, item);
		
	});
}
