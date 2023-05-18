#pragma once
#include "CMSMessageDecorator.h"
#include "Configuration/MessageDecoratorConfiguration.h"


class MessageDecoratorFactory
{
public:
	CMSMessageDecorator* create(const MessageDecoratorConfiguration& config);
};

