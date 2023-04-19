#pragma once
#include "CMSMessageDecorator.h"
#include "Configuration/TestCaseProducerConfiguration.h"


class MessageDecoratorFactory
{
public:
	CMSMessageDecorator* create(const interoperability_tests::config::producer::MessageSenderConfiguration& config);
};

