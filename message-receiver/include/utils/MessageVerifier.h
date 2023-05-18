#pragma once

#include <Configuration/MessageDecoratorConfiguration.h>
#include <cms/Session.h>
#include <cms/Message.h>
#include <MessageContentVerifiers/ExpectedField.h>
#include <MessageContentVerifiers/FieldVerifierFactory.h>
#include <Notifier/TestNotifier.h>

class MessageVerifier
{
public:
	MessageVerifier(const std::string &id, const MessageDecoratorConfiguration& decoratorConfig, Notifier & parent);
	void verify(const cms::Message* message) const;
protected:
	std::vector<IExpectedField*> mVerifiers;

private:
	FieldVerifierFactory mVerifierFactory;
	const std::string mId;
	Notifier &mParent;
};

