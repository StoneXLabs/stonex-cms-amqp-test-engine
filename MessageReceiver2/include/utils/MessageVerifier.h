#pragma once

#include <Configuration/MessageDecoratorConfiguration.h>
#include <cms/Session.h>
#include <cms/Message.h>
#include <MessageContentVerifiers/ExpectedField.h>
#include <MessageContentVerifiers/FieldVerifierFactory.h>

class MessageVerifier
{
public:
	explicit MessageVerifier(const MessageDecoratorConfiguration& decoratorConfig);
	void verify(const cms::Message* message) const;
protected:
	std::vector<IExpectedField*> mVerifiers;

private:
	FieldVerifierFactory mVerifierFactory;
};

