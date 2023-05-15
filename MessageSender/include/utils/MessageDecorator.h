#pragma once

#include <Configuration/MessageDecoratorConfiguration.h>
#include <cms/Session.h>
#include <cms/Message.h>

class CMSMessageDecorator;

class MessageDecorator
{
public:
	explicit MessageDecorator(const MessageDecoratorConfiguration& decoratorConfig);
	void decorate(cms::Message* message, cms::Session* session) const;
protected:
	CMSMessageDecorator *mDecorator{ nullptr };
};

