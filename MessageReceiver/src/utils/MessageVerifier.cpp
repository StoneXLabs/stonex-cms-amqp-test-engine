#include <utils/MessageVerifier.h>
#include <MessageDecorator/MessageDecoratorFactory.h>
#include <fmt/format.h>

MessageVerifier::MessageVerifier(const std::string &id, const MessageDecoratorConfiguration & decoratorConfig, Notifier & parent)
	:mId{ id },
	mParent{ parent }
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
		if (!t)
			mParent.testEvent(EventStatus(false, mId, fmt::format("expected message field missing {} {}", to_string(item->expectedField()), item->fieldName())));
		else
			delete t;
	});
}
